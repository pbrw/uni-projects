#ifndef __LCD_H__
#define __LCD_H__ 1

#include <stm32.h>

/* Screen size in pixels, left top corner has coordinates (0, 0). */

#define LCD_PIXEL_WIDTH   130
#define LCD_PIXEL_HEIGHT  161

/* Some color definitions */

#define LCD_COLOR_WHITE    0xFFFF
#define LCD_COLOR_BLACK    0x0000
#define LCD_COLOR_GREY     0xF7DE
#define LCD_COLOR_BLUE     0x001F
#define LCD_COLOR_BLUE2    0x051F
#define LCD_COLOR_RED      0xF800
#define LCD_COLOR_MAGENTA  0xF81F
#define LCD_COLOR_GREEN    0x07E0
#define LCD_COLOR_CYAN     0x7FFF
#define LCD_COLOR_YELLOW   0xFFE0

void LCDconfigure(void);
void LCDclear(void);
void LCDgoto(int textLine, int charPos);
void LCDputchar(char c);
void LCDputcharWrap(char c);

void CS(uint32_t bit);
void LCDwriteData16(uint32_t data);
void LCDsetRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

#endif // __LCD_H__