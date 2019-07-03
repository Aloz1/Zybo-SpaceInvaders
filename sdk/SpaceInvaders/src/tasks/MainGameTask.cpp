/*
 * GameTask.cpp
 *
 *  Created on: 9Aug.,2018
 *      Author: alastair
 */

#include <cstdio>

#include "../config.h"
#include "../SpriteInstances.h"
#include "../drivers/VGA.h"
#include "MainGameTask.h"

using namespace CMSIS_CPP;

MainGameTask::MainGameTask() :
	TaskClass(nullptr, TaskPrio_HMI, configMINIMAL_STACK_SIZE),
	state(STATE_IDLE),
	psxReader(XPAR_PMOD_PSX_0_S_AXI_BASEADDR),
	invaderBinTask(
		{
			sprite_pack{&invaderSmall1Sprite, &invaderSmall2Sprite},
			sprite_pack{  &invaderMed1Sprite,   &invaderMed2Sprite},
			sprite_pack{  &invaderMed1Sprite,   &invaderMed2Sprite},
			sprite_pack{&invaderLarge1Sprite, &invaderLarge2Sprite},
			sprite_pack{&invaderLarge1Sprite, &invaderLarge2Sprite}
		}),
	score(0),
	high_score(0),
	life_count(3)
{
	reset_scheduled_cnt = xSemaphoreCreateCounting(MAX_TASK_CHILDREN, 0);
	reset_complete_cnt = xSemaphoreCreateCounting(MAX_TASK_CHILDREN, 0);

	playerTask.attach_maingame(this);
	invaderBinTask.attach_maingame(this);
}

// The game's task. Used by the FreeRTOS
void MainGameTask::task() {

	clearScreen(BLACK);
	draw_background(DEFAULT_COLOR);
	draw_score(DEFAULT_COLOR);
	draw_high_score(DEFAULT_COLOR);

	for(;;) {
		// Read the PSX controller
		psxReader.read(psxData);

		switch(state) {
			case STATE_IDLE:
				draw_idle();
				if(psxData.btnEx()) {
					state = STATE_RESET;
				}
				break;

			case STATE_RESET:
				// Reset game stuff
				score = 0;
				life_count = 3;

				// Inform other tasks of reset (they should call GameTask::notify_reset_scheduled())
				playerTask.reset();
				invaderBinTask.reset();

				// Draw life count
				draw_life_count(DEFAULT_COLOR);

				// Draw extra lives
				for(int i = 0; i < life_count; i++) {
					draw_life_sprite(i, PLAYER_COLOR);
				}



				state = STATE_PLAYING;
				break;

			case STATE_PLAYING:
				break;

			case STATE_GAMEOVER:
				break;
		}
		delay(MS_PER_FRAME);
	}
}

void MainGameTask::notify_reset_scheduled() {
	xSemaphoreGive(reset_scheduled_cnt);
}

void MainGameTask::notify_reset_complete() {
	xSemaphoreGive(reset_complete_cnt);
}

void MainGameTask::wait_reset_complete() {
	// Now wait for all tasks to finish resetting (synchronization)
	while(uxSemaphoreGetCount(reset_scheduled_cnt) > 0) {
		if(xSemaphoreTake(reset_scheduled_cnt, 0) == pdTRUE) {
			xSemaphoreTake(reset_complete_cnt, portMAX_DELAY);
		}
	}
}

PSXData MainGameTask::get_psx_data() {
	return psxData;
}

void MainGameTask::draw_uint(int x, int y, unsigned int val, uint8_t digits, uint8_t color, uint8_t bg_color) {
	// Convert int to string
	char buff[digits + 1];
	std::snprintf(buff, digits + 1, "%.*u", digits, val);

	// Draw high-score to screen
	drawString(x, y, buff, color, bg_color);
}

void MainGameTask::draw_score(uint8_t color) {
	draw_uint(SCORE_X, SCORE_Y, score, SCORE_DIGITS, color);
}

void MainGameTask::draw_high_score(uint8_t color) {
	draw_uint(HISCORE_X, HISCORE_Y, high_score, HISCORE_DIGITS, color);
}

void MainGameTask::draw_life_count(uint8_t color) {
	draw_uint(LIVES_X, LIVES_Y, life_count, 1, color);
}

void MainGameTask::draw_life_sprite(int pos, uint8_t color) {
	// Draw extra life
	playerSprite.draw(LIVES_X + CHAR_WIDTH + LINE_SPACING + pos * (playerSprite.width + LINE_SPACING), LIVES_Y, color);
}

void MainGameTask::draw_background(uint8_t color) {
	drawString(SCORE_TEXT_X, SCORE_TEXT_Y, SCORE_TEXT, color, BACKGROUND_COLOR);

	for(int x = WINDOW_LEFT; x <= WINDOW_RIGHT; x++) {
		drawPixel(x, PLAYAREA_BOTTOM, DEFAULT_COLOR);
	}
}

void MainGameTask::draw_idle() {

}

void MainGameTask::draw_game_over() {

}
