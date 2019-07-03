/*
 * PlayerTask.h
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

#ifndef SRC_TASKS_PLAYERTASK_H_
#define SRC_TASKS_PLAYERTASK_H_

#include "../drivers/PSXReader.h"
#include "PlayerLaserTask.h"
#include "GameTask.h"

class PlayerTask : public GameTask {
    // Player state.
	enum PlayerState {
		STATE_HIDDEN,
		STATE_ALIVE,
		STATE_DYING
	};

	enum PlayerMessage {
		MSG_NONE,
		MSG_RESET
	};

	PlayerLaserTask laserTask;
	PlayerState state;

	int x_pos;

	void draw(uint8_t color);

public:
	PlayerTask();
	void task();
	void reset();
};

#endif /* SRC_TASKS_PLAYERTASK_H_ */
