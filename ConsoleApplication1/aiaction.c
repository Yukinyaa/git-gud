#pragma once
#include"aiaction.h"

aiState *newState()
{
	aiState* x = NEW(aiState);
	x->nowaction = ACTION_GOSTRAIGHT;
	x->target.x = 0;
	x->target.x = 1;
}

coord2D nexttarget(int x, int y, int(apple[APPLE_COUNT][3]))
{
	int appledist[3] = { 0, };
	int minindex = -1;
	int smallest = INT_MAX;
	coord2D result;
	for (int i = 0; i<APPLE_COUNT; i++)
	{
		int dist = abs(apple[i][1] - x) + abs(apple[i][2] - y);
		if (smallest > dist)
		{
			smallest = dist;
			minindex = i;
		}
	}
	result.x = apple[minindex][1];
	result.y = apple[minindex][2];
	
	return result;
}



int _snakeAiAction(aiState *a, int(apple[APPLE_COUNT][3]), int x, int y)
{
	if (((x == a->target.x) && (y == a->target.y)))
	{
		a->target = nexttarget(x, y, apple);
		a->nowaction = ACTION_GOSTRAIGHT;
		a->movestart.x = x;
		a->movestart.y = y;

		gotoxy(0,23);
		printf("set target to : %d, %d", a->target.x, a->target.y);
	}

	int dx = x - a->movestart.x;
	int dy = y - a->movestart.y;
	int ddx, ddy;


	ddx = a->target.x - a->movestart.x;
	ddy = a->target.y - a->movestart.y;

	int updirection = DIRECTION_UP;
	int downdirection = DIRECTION_DOWN;
	int leftdirection = DIRECTION_LEFT;
	int rightdirection = DIRECTION_RIGHT;
	
	if (ddy < 0)
	{
		updirection = DIRECTION_DOWN;
		downdirection = DIRECTION_UP;
	}
	if (ddx < 0)
	{
		leftdirection = DIRECTION_RIGHT;
		rightdirection = DIRECTION_LEFT;
	}

	switch (a->nowaction)
	{
	case ACTION_GOSTRAIGHT:
		gotoxy(0, 24);
		printf("dx : %d", dx);
		if (x- a->target.x != 0)
			return rightdirection;
		else
			return downdirection;
		break;
	case ACTION_WOBBLETO:
		int targetdirection = DIRECTION_LEFT;

		/*if (dx % 2 && a->target.y - y == 1)
		{
			a->movestart.x = x;
			a->movestart.y = y;
			dx = x - a->movestart.x;
			dy = y - a->movestart.y;
		}*/

		if (y == 1)
		{
			switch (abs(dx % 2) + abs(dy % 2 * 2))
			{
			case 0:
				return updirection;
			case 1:
				return leftdirection;
			case 2:
				return downdirection;
			case 3:
				return rightdirection;
			}
		}
		if (dx<0)
			targetdirection == DIRECTION_RIGHT;

		else if (dx % 2)//==1
		{
			if (dy == 0)
				return rightdirection;
			return updirection;
		}
		else // if x % 2 == 0
		{
			if (y == a->target.y)
				return rightdirection;
			return downdirection;
		}
		break;
	}
	return -1;
}
