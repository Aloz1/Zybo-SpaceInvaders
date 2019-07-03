#ifndef _VGA_H_
#define _VGA_H_

#include <stdint.h>
#include "../config.h"

// Draw a pixel of the given colour
void drawPixel(int x, int y, uint8_t colour=WHITE);

// Draw a box of the given colour
void drawBox(int x1, int y1, int x2, int y2, uint8_t colour=WHITE);

// Draw a single character on the screen
void drawChar( int x, int y, char ch, uint8_t colour=WHITE, uint8_t background=BLACK );

// Draw a string of characters on the screen
void drawString( int x, int y, const char *s, uint8_t colour=WHITE, uint8_t background=BLACK );

// Clear the screen (to the given colour)
void clearScreen(uint8_t colour = BLACK);

// User additions
// Draw a circle of the given colour
void drawCircle(int x0, int y0, int r, uint8_t colour=WHITE);

#endif
