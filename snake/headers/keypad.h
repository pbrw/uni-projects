#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include <stm32.h>

/* Bitmask of the rows pins used in configuration */ 
#define ROWS_BITMASK (EXTI_PR_PR6 | EXTI_PR_PR7 | EXTI_PR_PR8 | EXTI_PR_PR9)

void setColumnsState(uint8_t state);
int16_t getActiveButton();
void EXTI9_5_IRQHandler(void);
void keypadConfigure();

#endif // __KEYPAD_H__
