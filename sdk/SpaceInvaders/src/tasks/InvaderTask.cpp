/*
 * SmallInvaderTask.cpp
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

#include "InvaderTask.h"
#include "PlayerLaserTask.h"
#include "../SpriteInstances.h"

#include <limits>

using namespace CMSIS_CPP;

// Constructor. Initialize the task (parent class) and other relevant data.
InvaderTask::InvaderTask() :
	state(STATE_HIDDEN),
	invaderSprite1(nullptr),
	invaderSprite2(nullptr),
	fg_color(DEFAULT_COLOR)
{}

// Setup pointers to sprites.
void InvaderTask::setSprites(Sprite *sprite1, Sprite *sprite2) {
	invaderSprite1 = sprite1;
	invaderSprite2 = sprite2;
}

// Set invader colour. Colours are as defined in VGA.h
void InvaderTask::setColor(uint8_t color) {
	fg_color = color;
}

// The invader's task
void InvaderTask::task() {

	for(;;) {
        // Wait indefinitely for a message to be sent from another task.
		uint32_t msg = MSG_NONE;
		xTaskNotifyWait(0, std::numeric_limits<uint32_t>::max(), &msg, portMAX_DELAY);

        // If a MSG_RESET has been received, reset the invader and skip the rest of this
        // loop iteration.
        if (msg == MSG_RESET) {
            oddSprite = true;
            state = STATE_MOVING;

            continue;
        }

		switch(state) {
			case STATE_HIDDEN:
                // Do nothing.
				break;

			case STATE_MOVING:
				if (msg == MSG_EXPLODE) {

					// Clear and draw explosion
					draw(BACKGROUND_COLOR);
					draw_explode(fg_color);

					// Delay for explosion duration
					delay(EXPLOSION_MS);

					// Clear explosion and move to hidden state
					draw_explode(BACKGROUND_COLOR);
					state = STATE_HIDDEN;

				} else if(msg == MSG_MOVE) {
                    // Clear the screen
					draw(BACKGROUND_COLOR);

					// TODO: DX and DY stuff here
                    
                    // Toggle the sprite shown
					oddSprite = !oddSprite;

                    // Redraw the sprite
					draw(fg_color);
				}

				break;
		}
	}
}

bool InvaderTask::isHidden() {
	return state == STATE_HIDDEN;
}

// Reset routine. Informs the invader task that it needs to reset.
void InvaderTask::reset(int x, int y) {
	x_pos = x;
	y_pos = y;
    xTaskNotify(getHandle(), MSG_RESET, eSetValueWithOverwrite);
}

// Move routine. Informs the invader task it needs to move and redraw.
void InvaderTask::move() {
	if(state == STATE_MOVING) xTaskNotify(getHandle(), MSG_MOVE, eSetValueWithOverwrite);
}

// Collidable virtual callback method for collisions. Sends a MSG_EXPLODE.
void InvaderTask::onCollide() {
	if(state == STATE_MOVING) xTaskNotify(getHandle(), MSG_EXPLODE, eSetValueWithOverwrite);
}

// Collidable virtual method used to return the current sprite to check for collisions.
Sprite* InvaderTask::getSprite() {
	return (oddSprite ? invaderSprite1 : invaderSprite2);
}

// Draw the invader
void InvaderTask::draw(uint8_t color) {
	if (oddSprite && invaderSprite1 != nullptr)
		invaderSprite1->draw(x_pos, y_pos, color);
	else if (invaderSprite2 != nullptr)
		invaderSprite2->draw(x_pos, y_pos, color);
}

// Draw the invader explosion
void InvaderTask::draw_explode(uint8_t color) {
	int x = x_pos;
	int y = y_pos;

    // Centre align the explosion sprite to the invader sprite
	if (invaderSprite1 != nullptr) {
		x += (invaderSprite1->width - invaderExplodeSprite.width) / 2;
		y += (invaderSprite1->height - invaderExplodeSprite.height) / 2;
	}

    // Now draw
	invaderExplodeSprite.draw(x, y, color);
}

// Collidable virtual method
int InvaderTask::getX() {
	return x_pos;
}

// Collidable virtual method
int InvaderTask::getY() {
	return y_pos;
}

// Collidable virtual method
bool InvaderTask::disabled() {
	return isHidden();
}
