/*
 * PlayerLaserTask.h
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

#ifndef SRC_TASKS_PLAYERLASERTASK_H_
#define SRC_TASKS_PLAYERLASERTASK_H_

#include "../drivers/PSXReader.h"
#include "../drivers/VGA.h"
#include "../InvaderColumn.h"

#include "GameTask.h"

#include <FreeRTOS.h>
#include <semphr.h>

class Sprite;

class PlayerLaserTask : public GameTask, Collidable {
	enum LaserState {
		STATE_HIDDEN,
		STATE_MOVING
	};

	SemaphoreHandle_t fire_sem;

	LaserState state;

	int x_pos;
	int y_pos;

	std::size_t collidableCount;
	std::array<Collidable*, PLAYER_LASER_COLLIDABLE_BUFF_LEN> collidables;

	void onCollide() override;
	Sprite* getSprite() override;

	bool laserCollided();

public:
	PlayerLaserTask();
	void task();

	void attachCollidable(Collidable *collidable);

	void fire(uint8_t x_pos, uint8_t y_pos);

	bool isHidden();
	int getX() override;
	int getY() override;
	bool disabled() override;
};

#endif /* SRC_TASKS_PLAYERLASERTASK_H_ */
