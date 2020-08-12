#include <gpio.h>
#include <stm32.h>

#include "../headers/game_timer.h"
#include "../headers/game_manager.h"

/* Initial configuration of game timer */
void gameTimerConfigure() {
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

	__NOP();

	TIM4->CR1 = TIM_CR1_URS;
	TIM4->PSC = GT_PRESCALER - 1;
	TIM4->ARR = GT_AUTO_RELOAD - 1;
	TIM4->EGR = TIM_EGR_UG;	

	TIM4->SR = ~(TIM_SR_UIF);
	TIM4->DIER = TIM_DIER_UIE;

    TIM4->CR1 |= TIM_CR1_CEN;

    NVIC_EnableIRQ(TIM4_IRQn);
}

/* Interrupt handling function */
void TIM4_IRQHandler(void) {
	uint32_t it_status = TIM4->SR & TIM4->DIER;
	if (it_status & TIM_SR_UIF) {
		TIM4->SR &= ~TIM_SR_UIF;

        update();
	}
}