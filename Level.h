#pragma once
#include "conio2.h"

extern bool STOP_MUSIC;
extern int DIRECT;
extern bool SET_DIRECT;

struct Point {
	int x;
	int y;
};

class Level {
private:
	int scr_height;
	int scr_width;
	int backgroundColor;
	int foregroundColor;
public:
	Level(int bgColor = BLACK, int borderColor = DARKGRAY);
	void gameOver();
	int getBgColor();
	int getBorderColor();
	int getWidth();
	int getHeight();
	void updateScore(int score, int snakeColor);
};