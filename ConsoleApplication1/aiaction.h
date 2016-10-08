#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"varable.h"


typedef struct vector2D{
	int x, y;
}coord2D;

typedef int actionstate;
#define ACTION_WOBBLETO 2
#define ACTION_TOWALL 1
#define ACTION_GOSTRAIGHT 0


typedef struct AiState{
	int snakelength;
	coord2D target;
	coord2D movestart;
	actionstate nowaction;
}aiState;


aiState *newState();
coord2D nexttarget(int x, int y, int(apple[APPLE_COUNT][3]));
int _snakeAiAction(aiState *a, int(apple[APPLE_COUNT][3]), int x, int y);