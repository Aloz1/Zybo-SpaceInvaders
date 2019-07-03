/*
 * GameTask.h
 *
 *  Created on: 9Aug.,2018
 *      Author: alastair
 */

#ifndef SRC_TASKS_MAINGAMETASK_H_
#define SRC_TASKS_MAINGAMETASK_H_

#include "TaskCPP.h"
#include "../config.h"

#include "PlayerTask.h"
#include "InvaderBinTask.h"

#include <FreeRTOS.h>
#include <semphr.h>

class MainGameTask : public CMSIS_CPP::TaskClass {
	enum MainGameState {
		STATE_RESET,
		STATE_PLAYING,
		STATE_GAMEOVER,
		STATE_IDLE
	};

	MainGameState state;

	SemaphoreHandle_t reset_scheduled_cnt;
	SemaphoreHandle_t reset_complete_cnt;

	PSXReader psxReader;
	PSXData psxData;

	PlayerTask playerTask;
	InvaderBinTask<INVADER_COLUMNS, INVADER_ROWS> invaderBinTask;

	int score;
	int high_score;
	int life_count;

public:
	MainGameTask();

	void task();

	void notify_reset_scheduled();
	void notify_reset_complete();
	void wait_reset_complete();

	PSXData get_psx_data();

	void draw_uint(int x, int y, unsigned int val, uint8_t digits, uint8_t color, uint8_t bg_color = BACKGROUND_COLOR);
	void draw_score(uint8_t color);
	void draw_high_score(uint8_t color);
	void draw_life_count(uint8_t color);
	void draw_life_sprite(int pos, uint8_t color);
	void draw_background(uint8_t color);
	void draw_idle();
	void draw_game_over();
};

#endif /* SRC_TASKS_MAINGAMETASK_H_ */
