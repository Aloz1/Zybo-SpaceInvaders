/*
 * InvaderColumn.h
 *
 *  Created on: 22May,2018
 *      Author: alastair
 */

#ifndef SRC_TASKS_INVADERCOLUMN_H_
#define SRC_TASKS_INVADERCOLUMN_H_

#include <array>
#include <cstdint>

#include "config.h"
#include "Sprite.h"
#include "tasks/InvaderTask.h"

class PlayerLaserTask;

// For convenience
using sprite_pack = std::array<Sprite *const, INVADER_SPRITE_COUNT>;

// Template takes row count to know how many invaders need to be instantiated
template <std::size_t ROWS>
class InvaderColumn {

	std::array<InvaderTask, ROWS> invaders;

public:

	int invaderAliveCount();
	bool allInvadersDead();

	void setSprites(const std::array<const sprite_pack, ROWS> s);

	void reset(int x_pos);
	void attachCollidableToLaser(PlayerLaserTask &laser);
	void move();
};

// Returns the number of invaders within the column that are still alive
template <std::size_t ROWS>
int InvaderColumn<ROWS>::invaderAliveCount() {
	int n = 0;

	for (std::size_t i = 0; i < ROWS; i++) {
        // An invader is dead if it is hidden. Count all invaders that are
        // dead/hidden
		if(!invaders[i].isHidden())
			n++;
	}

	return n;
}

// Returns a boolean indicating whether or not all invaders are dead
template <std::size_t ROWS>
bool InvaderColumn<ROWS>::allInvadersDead() {
	return invaderAliveCount() == 0;
}

// Initializes sprites for each invader within the column
template <std::size_t ROWS>
void InvaderColumn<ROWS>::setSprites(const std::array<const sprite_pack, ROWS> s)  {
	for (std::size_t i = 0; i < ROWS; i++) {
		invaders[i].setSprites(s[i][0], s[i][1]);
	}
}

// Inform all invaders that it is now time to move
template <std::size_t ROWS>
void InvaderColumn<ROWS>::move() {
	for (std::size_t i = 0; i < ROWS; i++) {
		invaders[i].move();
	}
}

// Reset the position of all invaders. The x position is given to us by the caller,
// whereas the y position is calculated from constants within config.h and the number
// of rows.
template <std::size_t ROWS>
void InvaderColumn<ROWS>::reset(int x_pos) {
	for (std::size_t i = 0; i < ROWS; i++) {
		invaders[i].reset(x_pos, INVADER_BIN_Y + (INVADER_BIN_HEIGHT / ROWS) * i);
	}
}

// Attach invaders to the player laser task so that it can test if it has collided with anything.
template <std::size_t ROWS>
void InvaderColumn<ROWS>::attachCollidableToLaser(PlayerLaserTask &laser) {
	for (std::size_t i = 0; i < ROWS; i++) {
		laser.attachCollidable(&invaders[i]);
	}
}

#endif /* SRC_TASKS_INVADERCOLUMN_H_ */
