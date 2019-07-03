/*
 * GameTaskChild.cpp
 *
 *  Created on: 12Aug.,2018
 *      Author: alastair
 */

#include <FreeRTOS.h>

#include "GameTask.h"
#include "../config.h"

using namespace CMSIS_CPP;

GameTask::GameTask() :
	TaskClass(nullptr, TaskPrio_HMI, configMINIMAL_STACK_SIZE),
	main_game(nullptr),
	root(this),
	parent(nullptr)
{}

GameTask::~GameTask() {}

void GameTask::attach_maingame(MainGameTask *game) {
	main_game = game;
}

void GameTask::attach_parent(GameTask *new_parent) {
	parent = new_parent;
	main_game = root->main_game;
}

MainGameTask* GameTask::get_maingame() {
	return main_game;
}

GameTask* GameTask::get_root() {
	return root;
}

GameTask* GameTask::get_parent() {
	return parent;
}
