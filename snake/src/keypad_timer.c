#include <gpio.h>
#include <stm32.h>

#include "../headers/keypad.h"
#include "../headers/button.h"
#include "../headers/keypad_timer.h"


/* Initial configuration of keypad timer */
void keypadTimerConfigure() {
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	__NOP();

	TIM3->CR1 = TIM_CR1_URS;
	TIM3->PSC = KT_PRESCALER - 1;
	TIM3->ARR = KT_AUTO_RELOAD - 1;
	TIM3->EGR = TIM_EGR_UG;	

	TIM3->SR = ~(TIM_SR_UIF);
	TIM3->DIER = TIM_DIER_UIE;

    NVIC_EnableIRQ(TIM3_IRQn);
}


/* Enables or disables keypad timer */
void counterSetActive(int x) {
	if (x == 1) {
		TIM3->CR1 |= TIM_CR1_CEN;
	} else {
		TIM3->CR1 &= ~TIM_CR1_CEN;
	} 
}


/* Interrupt handling function */
void TIM3_IRQHandler(void) {
	uint32_t it_status = TIM3->SR & TIM3->DIER;
	if (it_status & TIM_SR_UIF) {
		TIM3->SR &= ~TIM_SR_UIF;

		int16_t activeButton = getActiveButton(); 
		if (activeButton == -1) {
            onRelease();

			counterSetActive(0);
			setColumnsState(0);
            
			EXTI->PR = ROWS_BITMASK; 
			EXTI->IMR |= ROWS_BITMASK;
		} else {
			onTick(activeButton);
        }
	}
}