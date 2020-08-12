#include "../headers/game_manager.h"
#include "../headers/lcd.h"

#include <string.h>
#include <stdlib.h>

/* 
    Unit responsible for the main logic of the game
*/

/*  Size of the single square tile in pixels */

#define FIELD_SIZE 8

/*  Number of rows and columns of fields */

#define BOARD_ROWS (LCD_PIXEL_WIDTH / FIELD_SIZE)
#define BOARD_COLUMNS (LCD_PIXEL_HEIGHT / FIELD_SIZE)


/*  Representation of the board: 
    -1  red square to be eaten by the snake
    0   white empy square
    >0  one of the snake's black squares, 
        numbered from head to tile with consecutive descending natural numbers
*/         
static int16_t board[BOARD_ROWS][BOARD_COLUMNS];

/*  Pair used when working with single field */
struct Field {
    int16_t row, column;
};

/*  First field of the snake */ 
static struct Field head;

/*  Last field of the snake */
static struct Field tail;

/* 
    Incremented when snake makes one step
    Used to assign new values to head of the snake
*/
static uint16_t fieldCounter;


/*
    Moving directions description
    > 0
    v 1
    < 2
    ^ 3
*/
#define DIRS_NUM 4

/*  Current direction */
static uint16_t direction;

/*  For convenient position calculation */ 
static int16_t cx[DIRS_NUM] = {0, -1, 0, 1};
static int16_t cy[DIRS_NUM] = {1, 0, -1, 0};

/*  Setup the initial state of the board */
static void setupBoard() {
    memset(board, 0, BOARD_ROWS * BOARD_COLUMNS * sizeof(int16_t));

    board[0][0] = 1;
    board[0][1] = 2;
    board[0][2] = 3;

    fieldCounter = 3;
    board[6][6] = -1;

    head.row = 0;
    head.column = 2;

    tail.row = 0;
    tail.column = 0;

    direction = 0;
}

/*  Print whole game board at once */
static void reprintScreen() {
    uint16_t boardWidth = BOARD_COLUMNS * FIELD_SIZE;
    uint16_t boardHeight = BOARD_ROWS * FIELD_SIZE;

    CS(0);
	LCDsetRectangle(0, 0, boardHeight - 1, boardWidth - 1);
        for (int j = 0; j < boardWidth; j++) {
    for (int i = 0; i < boardHeight; i++) {
			uint16_t fieldX = i / FIELD_SIZE;
            uint16_t fieldY = j / FIELD_SIZE;

            if (board[fieldX][fieldY] > 0) {
                LCDwriteData16(LCD_COLOR_BLACK);
            } else if (board[fieldX][fieldY] == -1) {
                LCDwriteData16(LCD_COLOR_RED);
            } else {
                LCDwriteData16(LCD_COLOR_WHITE);
            }
		}
	}
	CS(1);
}

/*  Restarts game */
void restartGame() {
    LCDclear();
    setupBoard();
    reprintScreen();
}


/*  Returns field after taking one step from origin in specific direction */
static struct Field move(struct Field origin, uint16_t direction) {
    origin.row += cx[direction] + BOARD_ROWS;
    while (origin.row >= BOARD_ROWS) origin.row -= BOARD_ROWS;

    origin.column += cy[direction] + BOARD_COLUMNS;
    while (origin.column >= BOARD_COLUMNS) origin.column -= BOARD_COLUMNS;

    return origin;
}


/*  Color specific field with the specific color on LCD display */
static void LCDcolorField(struct Field field, uint32_t color) {
    uint16_t beginRow = field.row * FIELD_SIZE;
    uint16_t beginColumn = field.column * FIELD_SIZE;
    
    CS(0);
	LCDsetRectangle(beginRow, beginColumn, beginRow + FIELD_SIZE - 1, beginColumn + FIELD_SIZE - 1);
    for (int j = 0; j < FIELD_SIZE; j++) {
        for (int i = 0; i < FIELD_SIZE; i++) {
            LCDwriteData16(color);
		}
	}
    CS(1);
}


/*  Handles removing the last field of snake */
static void removeTail() {
    struct Field newTail;
    int16_t actualValue = board[tail.row][tail.column];

    /* looking around for a new tail */
    for (int i = 0; i < DIRS_NUM; i++) {
        newTail = move(tail, i);
        if (board[newTail.row][newTail.column] == actualValue + 1) {
            break;
        }
    }

    board[tail.row][tail.column] = 0;
    LCDcolorField(tail, LCD_COLOR_WHITE);
    tail = newTail;
}


/*  Randomly finds new red square to be eaten */
static void setNewGoal() {
    struct Field goal;
    do {
        goal.row = rand() % BOARD_ROWS;
        goal.column = rand() % BOARD_COLUMNS;
    } while (board[goal.row][goal.column]);

    board[goal.row][goal.column] = -1;
    LCDcolorField(goal, LCD_COLOR_RED);
}


/*  Sets new snake head after taking a step */ 
static void setNewHead() {
    fieldCounter++;
    board[head.row][head.column] = fieldCounter;
    LCDcolorField(head, LCD_COLOR_BLACK);
}


/* 
    Function called every frame
    Moves snake one step in a current direction
*/
void update() {
    head = move(head, direction);

    if (board[head.row][head.column] > 0) {
        /* snake hit itself, game over */
        restartGame();
        return; 
    } else if (board[head.row][head.column] == 0) {
        /* snake just took a step */ 
        removeTail();
    } else {
        /* snake ate red square */
        setNewGoal();
    }

    setNewHead();
}

/* 
    React to user input
    symbol - character of the button
    pressed - 0 if single clic, 1 if longer pressed
*/
void input(char symbol, uint8_t pressed) {
    if (pressed) {
        restartGame();
        return;
    }

    switch (symbol)
    {
    case '2':
        if (direction != 1) {
            direction = 3;
        }
        break;

    case '6':
        if (direction != 2) {
            direction = 0;
        }
        break;
    
    case '8':
        if (direction != 3) {
            direction = 1;
        }
        break;
    
    case '4':
        if (direction != 0) {
            direction = 2;
        }
        break;
    
    default:
        break;
    }
}