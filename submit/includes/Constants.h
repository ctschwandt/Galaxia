#ifndef CONSTANTS_H
#define CONSTANTS_H

// game
const int FRAME_RATE = 60;
const int RATE = 1000 / FRAME_RATE;

// constants for whole surface
const double FACTOR = 1.7;
const int W = 640 * FACTOR;
const int H = 480 * FACTOR;

// laser
const int LASER_SPEED = 9;
const Color PLAYER_LASER_COLOR = {250, 150, 0};
const Color ENEMY_LASER_COLOR = {0, 250, 150};

// gameobject
const int SPEED = 6;

// player
const int DEFAULT_PLAYER_LIVES = 3;
const int PLAYER_ATTACK_DELAY = 15;
const int IV_FRAMES = RATE * 4;

// aliens
const int OFFSET = 10;
const int ALIEN_WIDTH = 32;
const int ALIEN_HEIGHT = 32;
const int ALIEN_ATTACK_DELAY = 15;
const int ALIEN_LASER_COUNT = 3;

// blues
//const int BLUES = 0;
const int BLUE_NUM_ROWS = 2;
const int BLUE_NUM_PER_ROW = 21;
const int BLUE_LEFT_W = (W - BLUE_NUM_PER_ROW * (ALIEN_WIDTH + OFFSET)) / 2;
const int BLUE_TOP_ROW_Y = H / 4;
const int BLUE_BOTTOM_ROW_Y = BLUE_TOP_ROW_Y + ALIEN_HEIGHT;

// purples
//const int PURPLES = 1;
const int PURPLE_NUM_PER_ROW = BLUE_NUM_PER_ROW - 2;
const int PURPLE_LEFT_W = BLUE_LEFT_W + (ALIEN_WIDTH + OFFSET);
const int PURPLE_BOTTOM_ROW_Y = BLUE_BOTTOM_ROW_Y - ALIEN_HEIGHT * (BLUE_NUM_ROWS - 1);

// reds
//const int REDS = 2;
/* const int RED_COUNT = 15; */
const int RED_LEFT_W = PURPLE_LEFT_W + ALIEN_WIDTH + OFFSET;
const int RED_BOTTOM_ROW_Y = PURPLE_BOTTOM_ROW_Y - ALIEN_HEIGHT;
const int RED_NUM_BOTTOM_ROW = (PURPLE_NUM_PER_ROW - 2) / 3;
const int RED_NUM_TOP_ROW = RED_NUM_BOTTOM_ROW * 2;

// yellows
//const int YELLOWS = 3;
const int YELLOW_COUNT = 4;
const int YELLOW_LEFT_W = RED_LEFT_W;
const int YELLOW_BOTTOM_ROW_Y = RED_BOTTOM_ROW_Y - ALIEN_HEIGHT;

// fleet
/* const int ALIEN_COUNT = BLUE_NUM_ROWS * BLUE_NUM_PER_ROW + PURPLE_NUM_PER_ROW; // + RED_COUNT + YELLOW_COUNT; */
const int ATTACK_PER_SECOND = 37;
const int ATTACK_RATE = FRAME_RATE * ATTACK_PER_SECOND;
const int SPAWN_OFFSET = ALIEN_HEIGHT * 14;

// explosion
const int DISSIPATE_TIMER = 15;
const int FADE_TIMER = 27;
const int DISS_SPEED = 1;
const int FALLING_SPEED = 3;

// hud
const int BOTTOM_OFFSET = 51;

#endif
