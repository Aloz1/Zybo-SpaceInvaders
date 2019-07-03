#include <algorithm>
#include "xparameters.h" // Hardware Register locations etc.
#include "VGA.h"

// The processor accesses the frame buffer directly as memory
#define FRAMEBUFFER ( (volatile uint8_t *)  XPAR_BRAM_0_BASEADDR)      // The frame buffer
//#define CONTROLLER  (*(volatile U16 *) XPAR_VGADISPLAYCONTROLLER_0_BASEADDR)  // The controller

#define BITS_PER_PIXEL  (2)
#define PIXELS_PER_BYTE (8/BITS_PER_PIXEL) 
 
static const uint8_t pattern[][8] =
{
0,0,0,0,0,0,0,0,// space 
0,16,16,16,16,16,0,16,// !
0,40,40,0,0,0,0,0,// "
0,40,40,254,40,254,40,40,// #
0,124,144,144,124,18,18,124,// $
0,112,82,116,8,30,42,78,// %
0,24,36,20,40,36,34,29,// &
0,8,8,0,0,0,0,0,// '
0,4,8,16,16,16,8,4,// (
0,16,8,4,4,4,8,16,// )
0,0,8,8,62,8,20,34,// *
0,0,8,8,62,8,8,0,// +
0,0,0,0,0,8,8,16,// ,
0,0,0,0,62,0,0,0,// -
0,0,0,0,0,0,12,12,// .
0,4,4,12,8,24,16,16,// /
0,60,66,66,90,66,66,60,// 0
0,8,24,8,8,8,8,28,// 1
0,28,34,2,4,8,16,62,// 2
0,60,2,2,60,2,2,60,// 3
0,12,20,36,68,126,4,4,// 4
0,124,64,64,124,2,2,124,// 5
0,60,64,64,124,66,66,60,// 6
0,126,2,2,4,8,16,32,// 7
0,60,66,66,126,66,66,60,// 8
0,60,66,66,62,2,2,60,// 9
0,0,24,24,0,24,24,0,// :
0,0,24,24,0,24,24,8,// ;
0,4,8,16,32,16,8,4,// <
0,0,126,0,0,126,0,0,// =
0,32,16,8,4,8,16,32,// >
0,56,68,68,8,16,0,16,// ?
0,124,130,186,170,190,128,124,// @
0,56,68,130,130,254,130,130,// A
0,252,130,130,252,130,130,252,// B
0,124,130,128,128,128,130,124,// C
0,248,132,130,130,130,132,248,// D
0,254,128,128,252,128,128,254,// E
0,254,128,128,252,128,128,128,// F
0,124,130,128,190,130,130,124,// G
0,130,130,130,254,130,130,130,// H
0,56,16,16,16,16,16,56,// I
0,62,8,8,8,8,72,48,// J
0,68,72,80,96,80,72,68,// K
0,64,64,64,64,64,64,124,// L
0,198,170,146,130,130,130,130,// M
0,130,194,162,146,138,134,130,// N
0,56,68,130,130,130,68,56,// O
0,252,130,130,130,252,128,128,// P
0,56,68,130,130,138,68,58,// Q
0,252,130,130,130,252,132,130,// R
0,124,128,128,124,2,2,124,// S
0,254,16,16,16,16,16,16,// T
0,130,130,130,130,130,198,56,// U
0,130,130,130,130,68,40,16,// V
0,130,130,130,130,146,170,198,// W
0,130,68,40,16,40,68,130,// X
0,130,68,40,16,16,16,16,// Y
0,254,4,8,16,32,64,254,// Z
0,24,16,16,16,16,16,24,// [
0,16,16,24,8,12,4,4,// backslash
0,24,8,8,8,8,8,24,// ]
0,0,8,20,34,0,0,0,// ^
0,0,0,0,0,0,126,0,// _
16,8,8,0,0,0,0,0,// `
0,0,0,0,0,0,0,0,// a Haven't time to do these!
0,0,0,0,0,0,0,0,// b
0,0,0,0,0,0,0,0,// c
0,0,0,0,0,0,0,0,// d
0,0,0,0,0,0,0,0,// e
0,0,0,0,0,0,0,0,// f
0,0,0,0,0,0,0,0,// g
0,0,0,0,0,0,0,0,// h
0,0,0,0,0,0,0,0,// i
0,0,0,0,0,0,0,0,// j
0,0,0,0,0,0,0,0,// k
0,0,0,0,0,0,0,0,// l
0,0,0,0,0,0,0,0,// m
0,0,0,0,0,0,0,0,// n
0,0,0,0,0,0,0,0,// o
0,0,0,0,0,0,0,0,// p
0,0,0,0,0,0,0,0,// q
0,0,0,0,0,0,0,0,// r
0,0,0,0,0,0,0,0,// s
0,0,0,0,0,0,0,0,// t
0,0,0,0,0,0,0,0,// u
0,0,0,0,0,0,0,0,// v
0,0,0,0,0,0,0,0,// w
0,0,0,0,0,0,0,0,// x
0,0,0,0,0,0,0,0,// y
0,0,0,0,0,0,0,0,// z
0,4,8,8,16,8,8,4,// {
0,8,8,8,8,8,8,8,// |
0,16,8,8,4,8,8,16,// }
0,0,0,96,146,12,0,0,// ~
};

// Clear the screen (to the given colour)
void clearScreen( uint8_t colour ) {
int x,y;
uint8_t  screenValue = (colour<<6)|(colour<<4)|(colour<<2)|(colour);

   for(x = 0; x < ROW_WIDTH/PIXELS_PER_BYTE; x++)
      for(y = 0; y < COL_HEIGHT; y++)
         FRAMEBUFFER[x+y*(ROW_WIDTH/PIXELS_PER_BYTE)] = screenValue;
}

// Draw a pixel of the given colour
void drawPixel(int x, int y, uint8_t colour) {

   uint8_t volatile *bytePtr = &(FRAMEBUFFER[x/PIXELS_PER_BYTE+y*(ROW_WIDTH/PIXELS_PER_BYTE)]);
   uint8_t mask = 0x3<<((3-(x&0x03))<<1);
   uint8_t mem  = *bytePtr;
   
   colour <<=     ((3-(x&0x03))<<1);
   colour  &= mask;
   mask     = ~mask;
   mem     &= mask;
   mem     |= colour;
   *bytePtr = mem;
}

// Draw a box of the given colour
void drawBox(int x1, int y1, int x2, int y2, uint8_t colour) {
int x,y;

   for(y = y1; y < y2; y++)
      for (x = x1; x < x2; x++) {
         drawPixel(x, y, colour);
//         uint8_t volatile *bytePtr = &(FRAMEBUFFER[x/PIXELS_PER_BYTE+y*(ROW_WIDTH/PIXELS_PER_BYTE)]);
//         uint8_t mask = 0x3<<7-(x%PIXELS_PER_BYTE);
//         colour <<= x%PIXELS_PER_BYTE;
//         *bytePtr = (*bytePtr&~mask) | (colour&mask);
         }
}

// Draw a single character on the screen
void drawChar( int x, int y, char ch, uint8_t colour , uint8_t background ) {

uint8_t const *theData = 0;
     
   if ((ch >= 'a') && (ch <= 'z')) // 'a' - 'z' => 'A' - 'Z'
     ch = ch-'a'+'A';
   if ((ch < ' ') && (ch > '~'))  // non-printing => '.'
     ch = '.';
     
   theData = pattern[ch-' '];

   for (int row = 0; row <=7; row++)
      for(int col = 0; col <= 7; col++)
         drawPixel(x+col, y+row, (theData[row]&(1<<(7-col)))?colour:background);
//         FRAMEBUFFER[x+col+(y+row)*ROW_WIDTH] = (theData[row]&(1<<(7-col)))?colour:background; 
}

// Draw a string of characters on the screen
void drawString( int x, int y, const char *s, uint8_t colour, uint8_t background ) {

   while (*s != '\0') {
      drawChar( x, y, *s++, colour, background );
      x += 8; // move across 8 pixels
      }
}


// Our additions

void drawHLine(int x0, int x1, int y, uint8_t color) {

	if (x0 > x1) {
		std::swap(x0, x1);
	}

	for(int x = x0; x < x1; x++) {
		drawPixel(x, y, color);
	}
}

void partialCircle(int xc, int yc, int x, int y, uint8_t color) {
	drawHLine(xc - x, xc + x, yc + y, color);   // First sector line
	drawHLine(xc - x, xc + x, yc - y, color);   // Second sector line
	drawHLine(xc - y, xc + y, yc + x, color);   // Third sector line
	drawHLine(xc - y, xc + y, yc - x, color);   // Forth sector line
}

void drawCircle(int x0, int y0, int r, uint8_t color) {
	int x = 0, y = r;
	int d = 3 - 2 * r;

	// First draw
	partialCircle(x0, y0, x, y, color);

	while(y >= x) {
		x++;

		if(d > 0) {
			y--;
			d += 4 * (x - y) + 10;
		} else {
			d += 4 * x + 6;
		}

		partialCircle(x0, y0, x, y, color);
	}
}
