/*
 * config.h
 *
 *  Created on: 20May,2018
 *      Author: alastair
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_

// Some example Colours (2 bits/pixel => 4 colours)
#define BLACK (0x00)
#define RED   (0x01)
#define BLUE  (0x02)
#define WHITE (0x03)

#define BACKGROUND_COLOR (BLACK)
#define DEFAULT_COLOR    (WHITE)
#define PLAYER_COLOR     (BLUE)
#define SPECIAL_COLOR    (RED)

// Dimensions of the display in pixels
constexpr int ROW_WIDTH      = 256;
constexpr int COL_HEIGHT     = 240;

// Dimensions of a character, in pixels
constexpr int CHAR_WIDTH      = 8;
constexpr int CHAR_HEIGHT     = 8;
constexpr int LINE_SPACING    = 3;

// Dimensions of the screen
constexpr int WINDOW_TOP      = 1;            // NB: Apparently there is an off by 1 error in hardware for the Y-axis.
constexpr int WINDOW_BOTTOM   = COL_HEIGHT;
constexpr int WINDOW_LEFT     = 0;
constexpr int WINDOW_RIGHT    = ROW_WIDTH - 1;

constexpr char SCORE_TEXT[]   = " SCORE<1>  HI-SCORE ";
constexpr char SCORE_TEXT_LEN = (sizeof(SCORE_TEXT) - 1) * CHAR_WIDTH;
constexpr int  SCORE_TEXT_X   = (WINDOW_RIGHT - WINDOW_LEFT - SCORE_TEXT_LEN) / 2;
constexpr int  SCORE_TEXT_Y   = WINDOW_TOP + LINE_SPACING;

constexpr uint8_t SCORE_DIGITS   = 4;
constexpr uint8_t HISCORE_DIGITS = SCORE_DIGITS;
constexpr uint8_t LIVES_DIGITS   = 1;

constexpr int SCORE_X = SCORE_TEXT_X + (SCORE_TEXT_LEN / 2 - SCORE_DIGITS * CHAR_WIDTH) / 2;
constexpr int SCORE_Y = SCORE_TEXT_Y + CHAR_HEIGHT + LINE_SPACING;

constexpr int HISCORE_X = SCORE_TEXT_X + ((SCORE_TEXT_LEN * 3) / 2 - HISCORE_DIGITS * CHAR_WIDTH) / 2;
constexpr int HISCORE_Y = SCORE_Y;

constexpr int PLAYAREA_TOP    = SCORE_Y + CHAR_HEIGHT + 1;
constexpr int PLAYAREA_BOTTOM = WINDOW_BOTTOM - CHAR_HEIGHT - LINE_SPACING * 2;
constexpr int PLAYAREA_LEFT   = WINDOW_LEFT;
constexpr int PLAYAREA_RIGHT  = WINDOW_RIGHT;

constexpr int LIVES_X = WINDOW_LEFT + 10;
constexpr int LIVES_Y = PLAYAREA_BOTTOM + LINE_SPACING;

constexpr int PLAYER_X = PLAYAREA_BOTTOM + 1;

constexpr int MAX_TASK_CHILDREN = 100;

#define INVADER_SPRITE_COUNT (2)
#define INVADER_QUEUE_LENGTH (4)
#define INVADER_COLUMNS      (7)
#define INVADER_ROWS         (5)

#define INVADER_BIN_WIDTH   (200)
#define INVADER_BIN_HEIGHT  (100)

#define INVADER_INITIAL_MS  (500)
#define INVADER_FINAL_MS    (100)

#define INVADER_BIN_X       ((WINDOW_LEFT + WINDOW_RIGHT - INVADER_BIN_WIDTH) / 2)
#define INVADER_BIN_Y       (50)

#define PLAYER_LASER_COLLIDABLE_BUFF_LEN (50)

#define BARRIER_HEIGHT (40)

#define MS_PER_FRAME                (40)
#define PLAYER_PX_PER_FRAME          (2)
#define INVADER_LASER_PX_PER_FRAME   (4)
#define PLAYER_LASER_PX_PER_FRAME    (8)
#define EXPLOSION_MS               (100)

#endif /* SRC_CONFIG_H_ */
