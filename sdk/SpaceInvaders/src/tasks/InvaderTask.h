/*
 * InvaderTask.h
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

#ifndef SRC_TASKS_INVADERTASK_H_
#define SRC_TASKS_INVADERTASK_H_

#include "../Sprite.h"
#include "../config.h"
#include "../Collidable.h"

#include "GameTask.h"

#include <FreeRTOS.h>
#include <semphr.h>

class InvaderTask : public GameTask, public Collidable {
	enum InvaderState {
		STATE_HIDDEN,
		STATE_MOVING
	};

    // All possible messages that are able to be sent to the invader.
	enum InvaderMessage {
		MSG_NONE,
		MSG_MOVE,
		MSG_EXPLODE,
		MSG_RESET
	};

	InvaderState state;

	Sprite *invaderSprite1;
	Sprite *invaderSprite2;

	uint8_t fg_color;
	int x_pos;
	int y_pos;

	bool oddSprite = true;

	void draw(uint8_t color);
	void draw_explode(uint8_t color);

	void onCollide() override;
	Sprite* getSprite() override;

public:
	InvaderTask();
	void setSprites(Sprite *sprite1, Sprite *sprite2);
	void setColor(uint8_t color);

	void task();

	bool isHidden();

	void reset(int x_pos, int y_pos);
	void move();
	void explode();

	int getX() override;
	int getY() override;
	bool disabled() override;
};

#endif /* SRC_TASKS_INVADERTASK_H_ */
