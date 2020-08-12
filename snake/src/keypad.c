#include <gpio.h>
#include <stm32.h>

#include "../headers/keypad.h"
#include "../headers/keypad_timer.h"

/* Keypad driver */

#define KEYPAD_GPIO GPIOC
#define ROWS_NUM 4
#define COLUMNS_NUM 4

/* Pin numbers attached to rows and columns */
static uint8_t rowPins [4] = {6, 7, 8, 9};
static uint8_t columnPins [4] = {0, 1, 2, 3};


/* Set specific state of column pin */ 
void setSingleColumnState(uint8_t columnPin, uint8_t state) {
	uint8_t offset = 16;
	if (state) offset = 0;

	KEYPAD_GPIO->BSRR = 1U << (columnPin + offset);
}

/* Set specific state for all columns */
void setColumnsState(uint8_t state) {
	for (int i = 0; i < COLUMNS_NUM; i++) {
		setSingleColumnState(columnPins[i], state);
	}
}

/* 
	Return number [0;3] of currently active row
	Return -1 if none of then is active
*/
int16_t getActiveRow(uint8_t columnPin) {
	setSingleColumnState(columnPin, 0);
	for (int i = 0; i < 10; i++) __NOP();
	uint16_t reg = KEYPAD_GPIO->IDR;
	setSingleColumnState(columnPin, 1);

	int16_t res = -1;
	for (int16_t i = 0; i < ROWS_NUM; i++) {
		if ((reg & (1U << rowPins[i])) == 0) {
			res = i;
		}
	}

	return res;
}

/* 
	Return ID of currently active button
	Return -1 if none of them is active
*/
int16_t getActiveButton() {
	int16_t res = -1;

	for (int16_t i = 0; i < COLUMNS_NUM; i++) {
		int16_t activeRowNum = getActiveRow(columnPins[i]);
		if (activeRowNum != -1) {
			res = activeRowNum * COLUMNS_NUM + i;
		}
	}

	return res;
}

/* Interrupt handling function */
void EXTI9_5_IRQHandler(void) {
	EXTI->IMR &= ~ROWS_BITMASK;
	EXTI->PR = ROWS_BITMASK;

	setColumnsState(1);

	TIM3->CNT = 0;
	counterSetActive(1);
}

/* Initial configuration of the keypad */
void keypadConfigure() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    __NOP();

	setColumnsState(0);

	for (int i = 0; i < COLUMNS_NUM; i++) {
		GPIOoutConfigure(
			KEYPAD_GPIO,
			columnPins[i],
			GPIO_OType_PP,
			GPIO_Low_Speed,
			GPIO_PuPd_NOPULL
        );
	}

	for (int i = 0; i < ROWS_NUM; i++) {
		GPIOinConfigure(
			KEYPAD_GPIO,
			rowPins[i],
			GPIO_PuPd_UP,
		    EXTI_Mode_Interrupt,
		    EXTI_Trigger_Falling
		);
	}

    EXTI->PR = ROWS_BITMASK;

	NVIC_EnableIRQ(EXTI9_5_IRQn);
}
