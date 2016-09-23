#pragma comment( lib, "libconio_64.a" )
#include "conio2.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <thread>
#include <windows.h>
#include <vector>
#include <ctime>

using namespace std;
bool STOP_MUSIC = false;
int DIRECT;
bool SET_DIRECT = true;;

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

class Level2 {
private:
	int scr_height;
	int scr_width;
	int backgroundColor;
	int foregroundColor;
public:
	Level2(int bgColor = BLACK, int borderColor = DARKGRAY) {
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

	void gameOver() {
		STOP_MUSIC = true;
		DIRECT = 0;
		gotoxy(1, 1);
		textcolor(backgroundColor);
		textbackground(foregroundColor);
		cout << "Game Over";
	}
	int getBgColor() {
		return backgroundColor;
	}
	int getBorderColor() {
		return foregroundColor;
	}
	int getWidth() {
		return scr_width;
	}
	int getHeight() {
		return scr_height;
	}

	void updateScore(int score, int snakeColor) {
		gotoxy(getWidth() / 2 - 5, 1);
		textbackground(foregroundColor);
		textcolor(BLACK);
		cout << "Score: " << score;
		textcolor(snakeColor);
		textbackground(backgroundColor);
	}
};

class Food2 {
private:
	struct Point {
		int x;
		int y;
	};
	int max_width;
	int max_height;
	Point location;
	int image;
	int color;
public:
	Point getPos() {
		return location;
	}

	void changePos(int x = 0, int y = 0) {
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

	int getColor() {
		return color;
	}

	Food2(Level2 lvl, int x, int y, int img = 260, int color = GREEN) {
		location.x = x;
		location.y = y;
		image = img;
		max_width = lvl.getWidth();
		max_height = lvl.getHeight();
		this->color = color;
		changePos(x, y);
	}

	void update() {
		textcolor(color);
		gotoxy(location.x, location.y);
		printf("%c", image);
	}
};

class Snake2 {
private:
	struct Point {
		int x;
		int y;
	};
	int image;
	vector<Point> location;
	int moving_direction;
	int lvl_width, lvl_height;
	int color;
public: 
	int getImage() {
		return image;
	}
	Point getHeadPos() {
		return location.back();
	}

	Point getTailPos() {
		return location[0];
	}
	int getColor() {
		return color;
	}

	Snake2(Level2 lvl, int x = 2, int y = 2, int img = 178, int color = GREEN) {
		image = img;
		gotoxy(x, y);
		location.push_back({ x, y });
		this->color = color;
		textcolor(color);
		lvl_height = lvl.getHeight();
		lvl_width = lvl.getWidth();
	}

	void removeLast() {
		location.erase(location.begin());
	}

	void addCurrent() {
		location.push_back({ wherex(), wherey() });
	}

	int getLength() {
		return location.size();
	}

	bool isMoveAllowed() {
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
};

void movement(Snake2 snake, Food2 food, Level2 lvl) {
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
				lvl.gameOver();
				gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
				return;
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
				lvl.gameOver();
				gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
				return;
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
				lvl.gameOver();
				gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
				return;
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
				lvl.gameOver();
				gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
				return;
			}
			break;
		}
		food.update();
		textcolor(snake.getColor());
		gotoxy(snake.getHeadPos().x, snake.getHeadPos().y);
		Sleep(100);
	}
}

int main() {
	//Prepare level
	Level2 level(BLACK, DARKGRAY);														

	//Initialize food; Image = 260 - diament | 259 - serce | 271 - s³oñce | 270 - nuta | 42 - gwiazdka
	Food2 food(level, 0, 0, 260, GREEN);

	//Initialize snake;
	Snake2 snake(level, 2, 2, 178, GREEN);
	
	thread musicThread(music);
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
	musicThread.join();
	movementThread.join();
	while (getch() != 27) {}
	return 0;
}