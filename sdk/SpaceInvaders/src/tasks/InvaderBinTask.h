/*
 * InvaderBinTask.h
 *
 *  Created on: 21May,2018
 *      Author: alastair
 */

#ifndef SRC_TASKS_INVADERBINTASK_H_
#define SRC_TASKS_INVADERBINTASK_H_

#include <array>
#include <cstdint>

#include "../InvaderColumn.h"
#include "../Sprite.h"

#include "GameTask.h"

template<std::size_t COLUMNS, std::size_t ROWS>
class InvaderBinTask : public GameTask {

    // States this task can be in
	enum BinState {
		STATE_WON,
		STATE_LOST,
		STATE_PLAYING
	};

    // Array of invader columns. Size dictated by template parameters
	std::array<InvaderColumn<ROWS>, COLUMNS> invaderColumns;

    // Index of left and right columns
	std::size_t leftColumnIdx;
	std::size_t rightColumnIdx;

	BinState state;

	int delayTimeMS();
	int invaderCount();

public:
	constexpr InvaderBinTask(const std::array<const sprite_pack, ROWS> s);

	void task();
	void reset();

	void attachCollidablesToLaser(PlayerLaserTask &laser);
};

// Constructor. Initializes invader columns with given column data.
template<std::size_t COLUMNS, std::size_t ROWS>
constexpr InvaderBinTask<COLUMNS, ROWS>::InvaderBinTask(const std::array<const sprite_pack, ROWS> s) :
	leftColumnIdx(0),
	rightColumnIdx(COLUMNS - 1),
	state(STATE_PLAYING)
{
	for(std::size_t i = 0; i < COLUMNS; i++) {
		invaderColumns.at(i).setSprites(s);
	}
}

// Task, executed by FreeRTOS' task framework
template<std::size_t COLUMNS, std::size_t ROWS>
void InvaderBinTask<COLUMNS, ROWS>::task() {
	for(;;) {
		switch(state) {
			case STATE_WON:
			case STATE_LOST:
                // Not yet implemented
				break;

			case STATE_PLAYING:
                // Check that the left most column still has invaders in it. If not,
                // iterate to the right until a column is found with invaders or
                // until there are no more columns left.
				while (invaderColumns[leftColumnIdx].allInvadersDead() && leftColumnIdx <= rightColumnIdx) {
					leftColumnIdx++;
				}

                // Check that the right most column still has invaders in it. If not,
                // iterate to the left until a column is found with invaders or
                // until there are no more columns left.
				while (invaderColumns[rightColumnIdx].allInvadersDead() && rightColumnIdx >= leftColumnIdx) {
					rightColumnIdx--;
				}

				// Break early if there aren't any invaders left.
				if (leftColumnIdx > rightColumnIdx) {
					state = STATE_WON;
					break;
				}

                // Inform all invaders that they need to move/update.
				for (std::size_t i = 0; i < COLUMNS; i++) {
					invaderColumns[i].move();
				}

				break;
		}

        // Delay for an amount of time. Delay time depends on the number of invaders still alive.
		delay(delayTimeMS());
	}
}

// Attach all child invader tasks to the player laser
template<std::size_t COLUMNS, std::size_t ROWS>
void InvaderBinTask<COLUMNS, ROWS>::attachCollidablesToLaser(PlayerLaserTask &laser) {
	for(std::size_t i = 0; i < COLUMNS; i++) {
		invaderColumns[i].attachCollidableToLaser(laser);
	}
}

// Reset invaders and state. This resets the X position of each invader column.
template<std::size_t COLUMNS, std::size_t ROWS>
void InvaderBinTask<COLUMNS, ROWS>::reset() {
	for(std::size_t i = 0; i < COLUMNS; i++) {
		invaderColumns[i].reset(INVADER_BIN_X + (INVADER_BIN_WIDTH / COLUMNS) * i);
	}

	state = STATE_PLAYING;
}

// Calculate the task delay in MS. This depends on the number of invaders still on the screen.
template<std::size_t COLUMNS, std::size_t ROWS>
int InvaderBinTask<COLUMNS, ROWS>::delayTimeMS() {
	return INVADER_FINAL_MS + ((INVADER_INITIAL_MS - INVADER_FINAL_MS) / (COLUMNS * ROWS)) * (invaderCount() - 1);
}

// Get the total number of invaders still on screen.
template<std::size_t COLUMNS, std::size_t ROWS>
int InvaderBinTask<COLUMNS, ROWS>::invaderCount() {
	int n = 0;

	for(std::size_t i = 0; i < COLUMNS; i++) {
		n += invaderColumns[i].invaderAliveCount();
	}

	return n;
}
#endif /* SRC_TASKS_INVADERBINTASK_H_ */
