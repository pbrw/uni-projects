#include <gpio.h>
#include <stm32.h>

#include "../headers/button.h"
#include "../headers/game_manager.h"

/* Information about keypad buttons */
static struct Button buttons[BUTTONS_NUM];

/* Assign character info to buttons */
void setupButtons() {
    buttons[0].symbol = '1';
    buttons[1].symbol = '2';
    buttons[2].symbol = '3';
    buttons[3].symbol = 'A';
    buttons[4].symbol = '4';
    buttons[5].symbol = '5';
    buttons[6].symbol = '6';
    buttons[7].symbol = 'B';
    buttons[8].symbol = '7';
    buttons[9].symbol = '8';
    buttons[10].symbol = '9';
    buttons[11].symbol = 'C';
    buttons[12].symbol = '*';
    buttons[13].symbol = '0';
    buttons[14].symbol = '#';
    buttons[15].symbol = 'D';
}

/* 
    Counter used to determine the length of
    the button activation time
*/
static uint32_t activationCounter = 0;

/* 
    Function called every timer tick if button is active 
    Checks if button is clicked or pressed
*/
void onTick(int16_t buttonId) {
    struct Button * button = &buttons[buttonId];

    if (activationCounter > button->lastActiveTime) {
        button->lastActiveTime = activationCounter;
        button->pressTime = 0;
    }

    if (button->pressTime == 0) {
        onClick(button);
    } else if (button->pressTime == PRESS_THRESHOLD) {
        onPress(button);
    }

    button->pressTime++;
}


/* Informs that none of the buttons is active */
void onRelease() {
    activationCounter++;
}


/* Specific button was clicked */
void onClick(struct Button * button) {
    input(button->symbol, 0);
}


/* Specific button was pressed */
void onPress(struct Button * button) {
    input(button->symbol, 1);
}