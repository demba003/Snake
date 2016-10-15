#pragma once
#include "Food.h"
#include "conio2.h"
#include <cstdio>
#include <ctime>

Point Food::getPos() {
	return location;
}

void Food::changePos(int x, int y) {
	srand(time(NULL));
	if (!x && !y) {
		x = (rand() % (max_width - 2)) + 2;
		y = (rand() % (max_height - 2)) + 2;
	}

	gotoxy(x, y);
	printf("%c", image);
	location.x = x;
	location.y = y;
}

int Food::getColor() {
	return color;
}

Food::Food(Level lvl, int x, int y, int img, int color) {
	location.x = x;
	location.y = y;
	image = img;
	max_width = lvl.getWidth();
	max_height = lvl.getHeight();
	this->color = color;
	changePos(x, y);
}

void Food::update() {
	textcolor(color);
	gotoxy(location.x, location.y);
	printf("%c", image);
}