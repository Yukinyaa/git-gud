#pragma once

#include<windows.h>

#define STATE_MENU 0
#define STATE_GAME 1
#define STATE_GAME_AI 2
#define STATE_GAME_EXIT 3

#define STATE_NEW_GAME_AI 7


#define WINDOW_X 68
#define WINDOW_Y 18
#define SPAN_X 1
#define SPAN_Y 1
#define WINDOW_CORNER WINDOW_X+SPAN_X+1 , WINDOW_Y+SPAN_Y+1

typedef int DIRCTION;
#define DIRECTION_UP	1
#define DIRECTION_DOWN	3
#define DIRECTION_LEFT	2
#define DIRECTION_RIGHT	0

#define TICKRATE 20

#define SNAKE_INITLENGTH 8


#define APPLE_COUNT 4

#define LINK_NULL (linksnake*)1

#define NEW(X) (X*)malloc(sizeof(X));

void gotoxy(int x, int y);