/*
 * Collidable.h
 *
 *  Created on: 22May,2018
 *      Author: alastair
 */

#ifndef SRC_TASKS_COLLIDABLE_H_
#define SRC_TASKS_COLLIDABLE_H_

#include "Sprite.h"

// Anything that is able to collide derives from this header
class Collidable {

    // Collision hook, called within checkCollided if a collision occurs
	virtual void onCollide() = 0;
public:

    // Simple box collision test
	bool checkCollided(Collidable &otherCollidable);

    // Self explanitory
	virtual Sprite* getSprite() = 0;
	virtual int getX() = 0;
	virtual int getY() = 0;
	virtual bool disabled() = 0;
};


#endif /* SRC_TASKS_COLLIDABLE_H_ */
