/*
 * Sprite.cpp
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */


#include "Sprite.h"
#include "drivers/VGA.h"

// Constructor, instantiates width, height and data.
Sprite::Sprite(const unsigned width, const unsigned height, const char *const data) :
	width(width),
	height(height),
	data(data)
{}

// Drawing function, iterates over pixel data for drawing to the screen. Pixels follow
// the Gimp indexed pixel format, resulting in simply 1's or 0's for pixels. Any pixel
// that is a 1 is drawn whilst any pixel with a 0 is ignored.
void Sprite::draw(uint8_t x, uint8_t y, uint8_t color) {
	for(uint8_t pix_y = 0; pix_y < height ; pix_y++) {
		for(uint8_t pix_x = 0; pix_x < width; pix_x++) {
			if (data[pix_x + pix_y * width]) drawPixel(pix_x + x, pix_y + y, color);
		}
	}
}
