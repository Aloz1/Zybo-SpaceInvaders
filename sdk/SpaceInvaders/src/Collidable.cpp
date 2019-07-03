/*
 * Collidable.cpp
 *
 *  Created on: 22May,2018
 *      Author: alastair
 */


#include "Collidable.h"

bool Collidable::checkCollided(Collidable &otherCollidable) {
    // Get sprites
	Sprite *sp1 = getSprite();
	Sprite *sp2 = otherCollidable.getSprite();

    // Get sprite 1 top-left and bottom-right corners
	int sp1_x1 = getX();
	int sp1_y1 = getY();
	int sp1_x2 = sp1_x1 + sp1->width - 1;
	int sp1_y2 = sp1_y1 + sp1->height - 1;

    // Get sprite 2 top-left and bottom-right corners
	int sp2_x1 = otherCollidable.getX();
	int sp2_y1 = otherCollidable.getY();
	int sp2_x2 = sp2_x1 + sp2->width - 1;
	int sp2_y2 = sp2_y1 + sp2->height - 1;

    // Check if collision occured
	bool collided = !disabled() && !otherCollidable.disabled()
			&& (sp1 != nullptr) && (sp2 != nullptr)
			&& sp1_x1 <= sp2_x2 && sp1_x2 >= sp2_x1
			&& sp1_y1 <= sp2_y2 && sp1_y2 >= sp2_y1;

    // Call collision hooks
	if (collided) {
		onCollide();
		otherCollidable.onCollide();
	}

    // Return result of collision check
	return collided;
}
