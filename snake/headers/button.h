#ifndef __BUTTON_H__
#define __BUTTON_H__

/* Number of buttons */
#define BUTTONS_NUM 16

/* Number of timer ticks to treat active button as pressed */
#define PRESS_THRESHOLD 15

/* 
	Buttons mapping [symbol-id]

	[1-0]   [2-1]   [3-2]   [A-3]

	[4-4]   [5-5]   [6-6]   [B-7]

	[7-8]   [8-9]   [9-10]  [C-11]

	[*-12]  [0-13]  [#-14]  [D-15]

*/

/* Information about single button */
struct Button {
	/* character written on the button */
	char symbol;
	/* how many timer ticks button has been active */
	uint32_t pressTime;
	/* last tick number of activation */
	uint32_t lastActiveTime; 
};

void setupButtons();
void onTick(int16_t buttonId);
void onClick(struct Button * button);
void onPress(struct Button * button);
void onRelease();

#endif // __BUTTON_H__