#pragma comment( lib, "libconio_64.a" )
#include "conio2.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <windows.h>
#include <vector>
#include <array>
#include <ctime>

using namespace std;
bool STOP_MUSIC = false;
int DIRECT;
bool SET_DIRECT = true;;
bool PAUSE = false;
struct text_info info;

void music()																			//function to play bg music in separate thread
{
	while (1) {
		if (STOP_MUSIC) break;
		Beep(1568, 200);
		Beep(1568, 200);
		Beep(1568, 200);
		Beep(1245, 1000);
		if (STOP_MUSIC) break;
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1397, 200);
		Beep(1175, 1000);
		if (STOP_MUSIC) break;
	}
}

struct Point {
	int x;
	int y;
};

struct Snake {
	int length;
	int image;
	vector<Point> location;
} snake;

void initSnake(int x, int y) {
	snake.length = 1;
	snake.image = 178;
	gotoxy(x, y);
	snake.location.push_back({ x, y });
	textcolor(GREEN);
}

struct Food {
	int pos_x, pos_y;
	int image;																			
} food;

void changeFoodPos(int x = 0, int y = 0) {
	srand(time(NULL));
	bool goodPos = false;

	if (!x && !y) {
		x = (rand() % (info.screenwidth - 2)) + 2;
		y = (rand() % (info.screenheight - 2)) + 2;
	}

	gotoxy(x, y);
	printf("%c", food.image);
	gotoxy(snake.location.back().x, snake.location.back().y);
	food.pos_x = x;
	food.pos_y = y;
}

void initFood(int x, int y, int img = 260) {
	food.pos_x = x;
	food.pos_y = y;
	food.image = img;
	changeFoodPos(x, y);
}

bool isMoveAllowed() {
	switch (DIRECT) {
	case 1:																				//up
		for (int i = 0; i < snake.location.size(); i++) {
			if (wherex() == snake.location[i].x && (wherey() - 1) == snake.location[i].y) return false;
		}
		if (wherey() == 2) return false;
		break;
	case 2:																				//down
		for (int i = 0; i < snake.location.size(); i++) {
			if (wherex() == snake.location[i].x && (wherey() + 1) == snake.location[i].y) return false;
		}
		if (wherey() == info.screenheight - 1) return false;
		break;
	case 3:																				//left
		for (int i = 0; i < snake.location.size(); i++) {
			if ((wherex() - 1) == snake.location[i].x && wherey() == snake.location[i].y) return false;
		}
		if (wherex() == 2) return false;
		break;
	case 4:																				//right
		for (int i = 0; i < snake.location.size(); i++) {
			if ((wherex() + 1) == snake.location[i].x && wherey() == snake.location[i].y) return false;
		}
		if (wherex() == info.screenwidth - 1) return false;
		break;
	}
	return true;
}


void SnakeMove() {
	while (!STOP_MUSIC) {
		if (STOP_MUSIC) break;
		switch (DIRECT) {
		case 1:																			//up
			if (isMoveAllowed()) {
				if (snake.location.back().x == food.pos_x && snake.location.back().y == food.pos_y) {
					snake.location.push_back({ wherex(), wherey() });
					printf("%c", snake.image);
					gotoxy(snake.location.back().x, snake.location.back().y - 1);
					snake.location.push_back({ wherex(), wherey() });
					changeFoodPos();
				}
				else {
					printf("%c", snake.image);
					gotoxy(snake.location[0].x, snake.location[0].y);
					printf("%s", " ");
					gotoxy(snake.location.back().x, snake.location.back().y - 1);
					snake.location.push_back({ wherex(), wherey() });
					snake.location.erase(snake.location.begin());
				}
				SET_DIRECT = true;
			}
			else {
				STOP_MUSIC = true;
				DIRECT = 0;
				gotoxy(1, 1);
				textcolor(BLACK);
				textbackground(DARKGRAY);
				cout << "Game Over";
				gotoxy(snake.location.back().x, snake.location.back().y);
				return;
			}
				
			break;
		case 2:																			//down
			if (isMoveAllowed()) {
				if (snake.location.back().x == food.pos_x && snake.location.back().y == food.pos_y) {
					snake.location.push_back({ wherex(), wherey() });
					printf("%c", snake.image);
					gotoxy(snake.location.back().x, snake.location.back().y + 1);
					snake.location.push_back({ wherex(), wherey() });
					changeFoodPos();
				}
				else {
					printf("%c", snake.image);
					gotoxy(snake.location[0].x, snake.location[0].y);
					printf("%s", " ");
					gotoxy(snake.location.back().x, snake.location.back().y + 1);
					snake.location.push_back({ wherex(), wherey() } );
					snake.location.erase(snake.location.begin());
				}
				SET_DIRECT = true;
			}
			else {
				STOP_MUSIC = true;
				DIRECT = 0;
				gotoxy(1, 1);
				textcolor(BLACK);
				textbackground(DARKGRAY);
				cout << "Game Over";
				gotoxy(snake.location.back().x, snake.location.back().y);
				return;
			}
			break;
		case 3:																			//left
			if (isMoveAllowed()) {
				if (snake.location.back().x == food.pos_x && snake.location.back().y == food.pos_y) {
					snake.location.push_back({ wherex(), wherey() });
					printf("%c", snake.image);
					gotoxy(snake.location.back().x - 1, snake.location.back().y);
					snake.location.push_back({ wherex(), wherey() });
					changeFoodPos();
				}
				else {
					printf("%c", snake.image);
					gotoxy(snake.location[0].x, snake.location[0].y);
					printf("%s", " ");
					gotoxy(snake.location.back().x - 1, snake.location.back().y);
					snake.location.push_back({ wherex(), wherey() });
					snake.location.erase(snake.location.begin());
				}
				SET_DIRECT = true;
			}
			else {
				STOP_MUSIC = true;
				DIRECT = 0;
				gotoxy(1, 1);
				textcolor(BLACK);
				textbackground(DARKGRAY);
				cout << "Game Over";
				gotoxy(snake.location.back().x, snake.location.back().y);
				return;
			}
			break;
		case 4:																			//right
			if (isMoveAllowed()) {
				if (snake.location.back().x == food.pos_x && snake.location.back().y == food.pos_y) {
					snake.location.push_back({ wherex(), wherey() });
					printf("%c", snake.image);
					snake.location.push_back({ wherex(), wherey() });
					changeFoodPos();
				}
				else {
					printf("%c", snake.image);
					gotoxy(snake.location[0].x, snake.location[0].y);
					printf("%s", " ");
					gotoxy(snake.location.back().x + 1, snake.location.back().y);
					snake.location.push_back({ wherex(), wherey() });
					snake.location.erase(snake.location.begin());
				}
				SET_DIRECT = true;
			}
			else {
				STOP_MUSIC = true;
				DIRECT = 0;
				gotoxy(1, 1);
				textcolor(BLACK);
				textbackground(DARKGRAY);
				cout << "Game Over";
				gotoxy(snake.location.back().x, snake.location.back().y);
				return;
			}
			break;
		}
		gotoxy(food.pos_x, food.pos_y);
		printf("%c", food.image);
		gotoxy(snake.location.back().x, snake.location.back().y);
		Sleep(100);
	}

}

void generate(int bgColor = BLACK, int borderColor = DARKGRAY) {
		int i;
		gettextinfo(&info);		 	   													// get the info about screen 
		_setcursortype(_SOLIDCURSOR);													// set cursor type
		clrscr();																		// clear the screen 
		gotoxy(1, 1);
		switchbackground(bgColor);														//set colors
		textcolor(borderColor);
		for (i = 1; i <= info.screenwidth; i++) printf("%c", 219);						// paint border around screen 
		gotoxy(1, info.screenheight);
		for (i = 0; i < info.screenwidth; i++) printf("%c", 219);
		for (i = 2; i < info.screenheight; i++) {
			gotoxy(1, i);
			printf("%c", 219);
			gotoxy(info.screenwidth, i);
			printf("%c", 219);
		}
		gotoxy(1, 1);
}

int main() {
	generate();																			//Prepare level

	initSnake(2, 2);																	//Initialize snake;

	initFood(0, 0);																		//Initialize food; Image = 260 - diament | 259 - serce | 271 - s³oñce | 270 - nuta | 42 - gwiazdka
	

	//thread musicThread(music);
	thread movementThread(SnakeMove);
	
	char userInput;

	while (1) {
		userInput = getch();
		if (STOP_MUSIC) break;
		switch (userInput) {
			case 27:
				//Wyjscie - Esc
				clrscr();
				STOP_MUSIC = true;
				cout << "Game Over";
				break;
			case 'p':	
				DIRECT = 0;
				break;
			case 'w':
				if (SET_DIRECT) {
					if (DIRECT != 2) {
						SET_DIRECT = false;
						DIRECT = 1;
					}
				}
				break;
			case 's':
				if (SET_DIRECT) {
					if (DIRECT != 1) {
						SET_DIRECT = false;
						DIRECT = 2;
					}
				}
				break;
			case 'a':
				if (SET_DIRECT) {
					if (DIRECT != 4) {
						SET_DIRECT = false;
						DIRECT = 3;
					}
				}
				break;
			case 'd':
				if (SET_DIRECT) {
					if (DIRECT != 3) {
						SET_DIRECT = false;
						DIRECT = 4;
					}
				}
				break;
			}
	}

	while (getch() != 27) {}

	//musicThread.join();
	movementThread.join();
	return 0;
}