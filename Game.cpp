#pragma comment( lib, "libconio_64.a" )
#include "conio2.h"
#include "Snake.h"
#include "Level.h"
#include "Food.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;
bool EASY_MODE = false;

//function to play bg music in separate thread
void music()
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



void movement(Snake snake, Food food, Level lvl) {
	while (!STOP_MUSIC) {
		if (STOP_MUSIC) break;
		switch (DIRECT) {
		case 1:																				//up
			if (snake.isMoveAllowed()) {
				if (snake.getHeadPos().x == food.getPos().x && snake.getHeadPos().y == food.getPos().y) {
					snake.addCurrent();
					printf("%c", snake.getImage());
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y - 1);
					food.changePos();
					lvl.updateScore(snake.getLength() - 1, snake.getColor());
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
				}
				else {
					printf("%c", snake.getImage());
					gotoxy(snake.getTailPos().x, snake.getTailPos().y);
					printf("%s", " ");
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y - 1);
					snake.addCurrent();
					snake.removeLast();
				}
				SET_DIRECT = true;
			}
			else {
				if (EASY_MODE) DIRECT = 0;
				else {
					lvl.gameOver();
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
					return;
				}
			}

			break;
		case 2:																				//down
			if (snake.isMoveAllowed()) {
				if (snake.getHeadPos().x == food.getPos().x && snake.getHeadPos().y == food.getPos().y) {
					snake.addCurrent();
					printf("%c", snake.getImage());
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y + 1);
					food.changePos();
					lvl.updateScore(snake.getLength() - 1, snake.getColor());
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
				}
				else {
					printf("%c", snake.getImage());
					gotoxy(snake.getTailPos().x, snake.getTailPos().y);
					printf("%s", " ");
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y + 1);
					snake.addCurrent();
					snake.removeLast();
				}
				SET_DIRECT = true;
			}
			else {
				if (EASY_MODE) DIRECT = 0;
				else {
					lvl.gameOver();
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
					return;
				}
			}
			break;
		case 3:																				//left
			if (snake.isMoveAllowed()) {
				if (snake.getHeadPos().x == food.getPos().x && snake.getHeadPos().y == food.getPos().y) {
					snake.addCurrent();
					printf("%c", snake.getImage());
					gotoxy(snake.getHeadPos().x - 1, snake.getHeadPos().y);
					food.changePos();
					lvl.updateScore(snake.getLength() - 1, snake.getColor());
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
				}
				else {
					printf("%c", snake.getImage());
					gotoxy(snake.getTailPos().x, snake.getTailPos().y);
					printf("%s", " ");
					gotoxy(snake.getHeadPos().x - 1, snake.getHeadPos().y);
					snake.addCurrent();
					snake.removeLast();
				}
				SET_DIRECT = true;
			}
			else {
				if (EASY_MODE) DIRECT = 0;
				else {
					lvl.gameOver();
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
					return;
				}
			}
			break;
		case 4:																				//right
			if (snake.isMoveAllowed()) {
				if (snake.getHeadPos().x == food.getPos().x && snake.getHeadPos().y == food.getPos().y) {
					snake.addCurrent();
					printf("%c", snake.getImage());
					food.changePos();
					lvl.updateScore(snake.getLength() - 1, snake.getColor());
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
				}
				else {
					printf("%c", snake.getImage());
					gotoxy(snake.getTailPos().x, snake.getTailPos().y);
					printf("%s", " ");
					gotoxy(snake.getHeadPos().x + 1, snake.getHeadPos().y);
					snake.addCurrent();
					snake.removeLast();
				}
				SET_DIRECT = true;
			}
			else {
				if (EASY_MODE) DIRECT = 0;
				else {
					lvl.gameOver();
					gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
					return;
				}
			}
			break;
		}
		food.update();
		textcolor(snake.getColor());
		gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
		Sleep(70);
	}
}

int main(int argc, char** argv) {
	if (argc != 1 && (!strcmp(argv[1], "easy") || !strcmp(argv[1], "EASY"))) EASY_MODE = true;
	
	//Prepare level
	Level level(BLACK, DARKGRAY);														

	//Initialize food; Image = 260 - diamond | 259 - heart | 271 - sun | 42 - star
	Food food(level, 0, 0, 260, GREEN);

	//Initialize snake;
	Snake snake(level, 2, 2, 178, GREEN);
	
	//thread musicThread(music);
	thread movementThread(movement, snake, food, level);
	
	char userInput;

	while (1) {
		userInput = getch();
		if (STOP_MUSIC) break;
		switch (userInput) {
			case 27:
				//Esc - pause
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
	//musicThread.join();
	movementThread.join();
	while (getch() != 27) {}
	clrscr();
	return 0;
}