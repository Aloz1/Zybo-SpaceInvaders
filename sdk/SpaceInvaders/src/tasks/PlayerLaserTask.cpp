/*
 * PlayerLaserTask.cpp
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

#include "PlayerLaserTask.h"

#include "../SpriteInstances.h"
#include "../config.h"

using namespace CMSIS_CPP;

// Default Constructor
PlayerLaserTask::PlayerLaserTask() :
	state(STATE_HIDDEN)
{
	fire_sem = xSemaphoreCreateBinary();
}

// Laser task
void PlayerLaserTask::task() {
	for(;;) {
		switch(state) {
			case STATE_HIDDEN:
                // Wait for another task to "give" the fire semaphore
				xSemaphoreTake(fire_sem, portMAX_DELAY);

                // Draw the laser and change to the moving state
				playerLaserSprite.draw(x_pos, y_pos, DEFAULT_COLOR);
				state = STATE_MOVING;
				break;

			case STATE_MOVING:
                // Clear the laser
				playerLaserSprite.draw(x_pos, y_pos, BACKGROUND_COLOR);

                // Change the position
				y_pos -= PLAYER_LASER_PX_PER_FRAME;

                // Check if we've hit the top or collided. If either of those
                // have happened, change  to the hidden state.
				if ((y_pos <= PLAYAREA_TOP) || laserCollided()) {
					state = STATE_HIDDEN;
					break;
				}

                // Redraw the laser
				playerLaserSprite.draw(x_pos, y_pos, DEFAULT_COLOR);
				break;
		}

        // Wait for a frame to pass before redrawing
		delay(MS_PER_FRAME);
	}
}

// Fire method, called externally by another task.
void PlayerLaserTask::fire(uint8_t x_start, uint8_t y_start) {
	if(isHidden()) {
        // Move the laser to the centre point given by the callee
        // (adjusted based off of laser sprite with and height.
		x_pos = x_start - playerLaserSprite.width / 2;
		y_pos = y_start - playerLaserSprite.height;

        // Let the laser task know it can now show the laser
		xSemaphoreGive(fire_sem);
	}
}

// Attach collidables to the laser
void PlayerLaserTask::attachCollidable(Collidable *c) {
    // Ensure collidable array isn't full before attaching
	if (collidableCount < PLAYER_LASER_COLLIDABLE_BUFF_LEN) {
        // Attach and increment count
		collidables[collidableCount] = c;
		collidableCount++;
	}
}

// Checks each collidable to see if a collision has occured
bool PlayerLaserTask::laserCollided() {
	for (std::size_t i = 0; i < collidableCount; i++) {
		if (collidables[i] != nullptr && collidables[i]->checkCollided(*this))
			return true;
	}

	return false;
}

bool PlayerLaserTask::isHidden() {
	return state == STATE_HIDDEN;
}

// Collidable virtual callback method
void PlayerLaserTask::onCollide() {
	state = STATE_HIDDEN;
}

// Collidable virtual method
Sprite* PlayerLaserTask::getSprite() {
	return &playerLaserSprite;
}

// Collidable virtual method
int PlayerLaserTask::getX() {
	return x_pos;
}

// Collidable virtual method
int PlayerLaserTask::getY() {
	return y_pos;
}

// Collidable virtual method
bool PlayerLaserTask::disabled() {
	return isHidden();
}
