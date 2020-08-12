#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <stm32.h>

void update();
void input(char symbol, uint8_t pressed);
void restartGame();

#endif // __GAME_MANAGER_H__