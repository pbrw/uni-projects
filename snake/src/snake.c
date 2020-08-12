#include "../headers/game_timer.h"
#include "../headers/keypad_timer.h"
#include "../headers/keypad.h"
#include "../headers/lcd.h"
#include "../headers/game_manager.h"
#include "../headers/button.h"

int main() {
    LCDconfigure();
    restartGame();
    keypadTimerConfigure();
    gameTimerConfigure();
    keypadConfigure();
    setupButtons();
    
    while (1) {}

    return 0;
}