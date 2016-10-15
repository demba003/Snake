#include "Snake.h"

int Snake::getImage() {
	return image;
}

Point Snake::getHeadPos() {
	return location.back();
}

Point Snake::getTailPos() {
	return location[0];
}

int Snake::getColor() {
	return color;
}

Snake::Snake(Level lvl, int x, int y, int img, int color) {
	image = img;
	gotoxy(x, y);
	location.push_back({ x, y });
	this->color = color;
	textcolor(color);
	lvl_height = lvl.getHeight();
	lvl_width = lvl.getWidth();
}

void Snake::removeLast() {
	location.erase(location.begin());
}

void Snake::addCurrent() {
	location.push_back({ wherex(), wherey() });
}

int Snake::getLength() {
	return location.size();
}

bool Snake::isMoveAllowed() {
	switch (DIRECT) {
	case 1:																				//up
		for (int i = 0; i < location.size(); i++) {
			if (wherex() == location[i].x && (wherey() - 1) == location[i].y) return false;
		}
		if (wherey() == 2) return false;
		break;
	case 2:																				//down
		for (int i = 0; i < location.size(); i++) {
			if (wherex() == location[i].x && (wherey() + 1) == location[i].y) return false;
		}
		if (wherey() == lvl_height - 1) return false;
		break;
	case 3:																				//left
		for (int i = 0; i < location.size(); i++) {
			if ((wherex() - 1) == location[i].x && wherey() == location[i].y) return false;
		}
		if (wherex() == 2) return false;
		break;
	case 4:																				//right
		for (int i = 0; i < location.size(); i++) {
			if ((wherex() + 1) == location[i].x && wherey() == location[i].y) return false;
		}
		if (wherex() == lvl_width - 1) return false;
		break;
	}
	return true;
}

int Snake::getDirection()
{
	return direction;
}
