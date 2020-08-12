#ifndef __GAME_TIMER_H__
#define __GAME_TIMER_H__

/*  Game timer cyclically updates game state */

/*  Timer frequency will be divided by this value */
#define GT_PRESCALER 16000

/* 
    Timer will update game state every given number of ms
    Responsible for snake speed 
*/
#define GT_AUTO_RELOAD 100

void gameTimerConfigure();
void TIM4_IRQHandler(void);

#endif // __GAME_TIMER_H__