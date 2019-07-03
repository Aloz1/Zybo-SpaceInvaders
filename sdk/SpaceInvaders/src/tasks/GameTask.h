/*
 * GameTaskChild.h
 *
 *  Created on: 12Aug.,2018
 *      Author: alastair
 */

#ifndef SRC_TASKS_GAMETASK_H_
#define SRC_TASKS_GAMETASK_H_

#include <FreeRTOS.h>
#include <semphr.h>
#include <array>

#include "TaskCPP.h"
#include "../config.h"

class MainGameTask;

class GameTask : public CMSIS_CPP::TaskClass {
	MainGameTask *main_game;
	GameTask *root;
	GameTask *parent;

	// TODO: Need to determine if "array" holds the number of valid children. Note,
	//       order is not important, so would be trivial to implement "removing" a node (simply swap with last child).
	std::array<GameTask*, MAX_TASK_CHILDREN> children;

public:
	GameTask();
	virtual ~GameTask();

	void attach_maingame(MainGameTask *gameTask);
	void attach_parent(GameTask *gameTask);

	MainGameTask* get_maingame();
	GameTask* get_root();
	GameTask* get_parent();
};

#endif /* SRC_TASKS_GAMETASK_H_ */
