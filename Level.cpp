#include "Level.h"
#include <cstdio>
#include <iostream>

using namespace std;

bool STOP_MUSIC = false;
int DIRECT;
bool SET_DIRECT = true;

Level::Level(int bgColor, int borderColor) {
	int i;
	struct text_info info;
	gettextinfo(&info);
	_setcursortype(_SOLIDCURSOR);
	clrscr();
	gotoxy(1, 1);
	switchbackground(bgColor);
	textcolor(borderColor);
	//paint border around screen 
	for (i = 1; i <= info.screenwidth; i++) printf("%c", 219);
	gotoxy(1, info.screenheight);
	for (i = 0; i < info.screenwidth; i++) printf("%c", 219);
	for (i = 2; i < info.screenheight; i++) {
		gotoxy(1, i);
		printf("%c", 219);
		gotoxy(info.screenwidth, i);
		printf("%c", 219);
	}
	gotoxy(1, 1);
	scr_height = info.screenheight;
	scr_width = info.screenwidth;
	backgroundColor = bgColor;
	foregroundColor = borderColor;
	updateScore(0, GREEN);
}

void Level::gameOver() {
	STOP_MUSIC = true;
	DIRECT = 0;
	gotoxy(1, 1);
	textcolor(backgroundColor);
	textbackground(foregroundColor);
	cout << "Game Over";
}

int Level::getBgColor() {
	return backgroundColor;
}

int Level::getBorderColor() {
	return foregroundColor;
}

int Level::getWidth() {
	return scr_width;
}

int Level::getHeight() {
	return scr_height;
}

void Level::updateScore(int score, int snakeColor) {
	gotoxy(getWidth() / 2 - 5, 1);
	textbackground(foregroundColor);
	textcolor(BLACK);
	cout << "Score: " << score;
	textcolor(snakeColor);
	textbackground(backgroundColor);
}
