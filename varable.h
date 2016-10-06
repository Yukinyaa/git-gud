#pragma once

#define STATE_MENU 0
#define STATE_GAME 1
#define STATE_GAME_AI 2
#define STATE_GAME_EXIT 3


#define WINDOW_X 68
#define WINDOW_Y 18
#define SPAN_X 1
#define SPAN_Y 1
#define WINDOW_CORNER WINDOW_X+SPAN_X+1 , WINDOW_Y+SPAN_Y+1

#define TICKRATE 20

#define SNAKE_INITLENGTH 8


#define APPLE_COUNT 4

#define LINK_NULL (linksnake*)1

void gotoxy(int x, int y) {
	COORD coord;

	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}