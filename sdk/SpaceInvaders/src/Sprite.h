/*
 * Sprite.h
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

#ifndef SRC_SPRITE_H_
#define SRC_SPRITE_H_

#include "stdint.h"

// Fairly trivial sprite container class
class Sprite {
public:
	const unsigned width;
	const unsigned height;
	const char *const data;

	Sprite(const unsigned width, const unsigned height, const char *const data);
	void draw(uint8_t x, uint8_t y, uint8_t color);
};


#endif /* SRC_SPRITE_H_ */
