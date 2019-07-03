/*
 * PlayerTask.cpp
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

#include <limits>

#include "PlayerTask.h"
#include "MainGameTask.h"

#include "../SpriteInstances.h"
#include "../config.h"

using namespace CMSIS_CPP;

// Constructor.
PlayerTask::PlayerTask() :
	state(STATE_HIDDEN),
	x_pos((PLAYAREA_RIGHT + PLAYAREA_LEFT) / 2)
{}

// Player task
void PlayerTask::task() {

	for(;;) {
		if(get_maingame() == nullptr) {
			return;
		}

		PSXData data = get_maingame()->get_psx_data();

		uint32_t msg = MSG_NONE;
		switch (state) {
			case STATE_HIDDEN:
				// Wait until told to wake up
				xTaskNotifyWait(0, std::numeric_limits<uint32_t>::max(), &msg, portMAX_DELAY);

				// Make sure message says RESET
				if(msg == MSG_RESET) {
					x_pos = (PLAYAREA_RIGHT + PLAYAREA_LEFT) / 2;
					draw(PLAYER_COLOR);
					state = STATE_ALIVE;
				}

				break;

			case STATE_ALIVE:

				// If the fire button has been pressed, signal the laser task, indicating where it should be placed.
				if(data.btnEx())
					laserTask.fire(x_pos + playerSprite.width / 2, PLAYAREA_BOTTOM - playerSprite.height);

				// If the left/right buttons are clicked, redraw the player at the new position
				if(data.btnLeft() || data.btnRight()) {
					// Clear player
					draw(BACKGROUND_COLOR);

					// Move the player
					if(data.btnLeft()) x_pos  -= PLAYER_PX_PER_FRAME;
					if(data.btnRight()) x_pos += PLAYER_PX_PER_FRAME;

					// If the player is off the screen, place them at the very edge.
					if(x_pos < PLAYAREA_LEFT) x_pos = 0;
					if((x_pos + playerSprite.width) > PLAYAREA_RIGHT) x_pos = PLAYAREA_RIGHT - playerSprite.width;

					// Redraw
					draw(PLAYER_COLOR);
				}
				break;

			case STATE_DYING:
				// TODO: Implement
				break;
		}
		// Wait for the next frame
		delay(MS_PER_FRAME);
	}
}

void PlayerTask::reset() {
    xTaskNotify(getHandle(), MSG_RESET, eSetValueWithOverwrite);
}

void PlayerTask::draw(uint8_t color) {
    // Draw, using current X pos and constant Y pos with the specified colour
	playerSprite.draw(x_pos, PLAYAREA_BOTTOM - playerSprite.height - 1, color);
}
