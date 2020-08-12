#ifndef __KEYPAD_TIMER_H__
#define __KEYPAD_TIMER_H__

/*  Keypad timer scans buttons cyclically */

/*  Timer frequency will be divided by this value */
#define KT_PRESCALER 16000

/*  Buttons state will be checked every number of ms */
#define KT_AUTO_RELOAD 30

void keypadTimerConfigure();
void counterSetActive(int x);
void TIM3_IRQHandler(void);

#endif // __KEYPAD_TIMER_H__