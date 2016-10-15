#pragma once
#include "Level.h"

class Food {
private:
	int max_width;
	int max_height;
	Point location;
	int image;
	int color;
public:
	Point getPos();
	void changePos(int x = 0, int y = 0);
	int getColor();
	Food(Level lvl, int x, int y, int img = 260, int color = GREEN);
	void update();
};