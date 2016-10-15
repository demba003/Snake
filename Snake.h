#pragma once
#include "conio2.h"
#include <vector>
#include "Level.h"

using namespace std;

class Snake {
private:
	int image;
	vector<Point> location;
	int moving_direction;
	int lvl_width, lvl_height;
	int color;
	int direction;
public:
	int getImage();
	Point getHeadPos();
	Point getTailPos();
	int getColor();
	Snake(Level lvl, int x = 2, int y = 2, int img = 178, int color = GREEN);
	void removeLast();
	void addCurrent();
	int getLength();
	bool isMoveAllowed();
	int getDirection();
};