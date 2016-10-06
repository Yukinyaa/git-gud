#pragma once

#include"varable.h"
#include"snakelink.h"




void printxy(int x, int y, char* str) {
	gotoxy(x + SPAN_X, y + SPAN_Y);
	printf(str);
	gotoxy(WINDOW_CORNER);                                              
}


int checksnake(int x,int y,linksnake *lnk)
{
	if (lnk == LINK_NULL)
		return 0;

	linksnake current = *lnk;
	if (current.x == x && current.y == y)
		return 1;
	return checksnake(x, y, current.prev);
}

void randapple(int (apple[APPLE_COUNT][3]))
{
	int i;
	for(i=0;i<APPLE_COUNT;i++)
	{
		if (!(apple)[i][0])
		{
			int x, y;
			int chk=0;
			do
			{
				x = rand() % WINDOW_X;
				y = rand() % WINDOW_Y;
				chk++;
				if (chk >= 10)
					return;
			} while (checksnake(x, y, getstart_snakelink(0)));
			apple[i][0] = 1;
			apple[i][1] = x;
			apple[i][2] = y;
			printxy(x, y, "A");
		}
	}
}


int ai_action(int x, int y)
{
	/*
	if (WINDOW_Y % 2 == 1 && x >= WINDOW_Y - 2)
	{
		
	}*/ //x가 홀수이면 조금 다른 패턴으로 작동해야 한다.
	if (y == 0)
	{
		if (x == 0)
			return 3;
		return 2;
	}
	
	else if (x % 2)//==1
	{
		if (y == 1 && x != WINDOW_X - 1)
			return 4;
		return 1;
	}
	else // if x % 2 == 0
	{
		if (y == WINDOW_Y )
			return 4;
		return 3;
	}
		
}
int resolvetick(int direction,int *length,int aimode,int reset)
{
	static int apple[APPLE_COUNT][3] = { {0,}, }; // apple[3] = {flag ,x ,y}
	static int x = WINDOW_X / 2, y = WINDOW_Y / 2;
	int i;
	static int ate_apple = 0;
	static int tick = 0;


	if (reset)
	{
		for (i = 0; i < APPLE_COUNT; i++)
		{
			apple[i][0] = 0;
		}
		x = WINDOW_X / 2, y = WINDOW_Y / 2;
	}


	randapple(apple);

	if (aimode)
	{
		direction = ai_action(x,y);
	}

	switch (direction%4)
	{
	case 1:
		if (y <= 0)return 1;
		y--;
		break;
	case 2:
		if (x <= 0)return 1;
		x--;
		break;
	case 3:
		if (y >= WINDOW_Y)return 1;
		y++;
		break;
	case 0:
		if (x >= WINDOW_X)return 1;
		x++;
		break;
	}
	if (checksnake(x, y,getstart_snakelink(0)))
		return 1;
	
	for (i = 0; i < APPLE_COUNT; i++)
	{
		if (apple[i][0]&&checksnake(apple[i][1], apple[i][2], getstart_snakelink(0)))
		{
			apple[i][0] = 0;
			ate_apple += 4;
		}
	}


	expand_snakelink(x,y);
	printxy(x, y, "@");
	
	for (i = 0; i < APPLE_COUNT; i++)
	{
		if (apple[i][0] == x && apple[i][1] == y)
		{
			apple[i][0] = 0; apple[i][1] = 0;
			ate_apple += 4;
		}
	}
	if (!(ate_apple)) {
		linksnake a= *getend_snakelink(0);
		printxy(a.x, a.y, " ");
		pop_snakelink();
	} else {
		ate_apple--;
		(*length)++;
	}

	return 0;
}

int resolvekeyboard(char key)
{
/*
    1|w
 2a-   - 4d
	3|
	s/x
*/
	switch (key)
	{
	case 'w':
		return 1;
	case 'a':
		return 2;
	case 's':	case 'x':
		return 3;
	case 'd':
		return 4;
	default:
		return 1;
	}
	return 1;
}

int gameover(int length) {
	printxy(20, 6, "■■■■■■■■■■■■■■■■■");
	gotoxy(20+1, 7+1); printf("■game over! score : %10d ■", length*100);
	printxy(20, 8, "■■■■■■■■■■■■■■■■■");
	_getch();
	return STATE_MENU;
}

void taduri() {
	int i = 0;

	int tx = 1, ty = 0;
	printxy(tx - SPAN_X, ty - SPAN_Y, (i++ % 2) ? "A" : "+");
	do
	{
		
		if (tx == 0)
			ty--;
		else if (ty == SPAN_Y + WINDOW_Y+1)
			tx--;
		else if (tx == SPAN_X + WINDOW_X + 1)
			ty++;
		else if (ty == 0)
			tx++;
		printxy(tx-SPAN_X, ty - SPAN_Y, (i++ % 2) ? "A" : "+");
	} while (!((tx == 0) & (ty == 0)));
}


int gameloop(int aimode)
{
	int x = WINDOW_X/2, y = WINDOW_Y/2;
	int pressedkey;
	int direction = 4;
	int length=SNAKE_INITLENGTH;
	
	static int tickrate = 1000 / TICKRATE;//2 tick/s
	int i=0;
	flushsnake();
	

	taduri();

	for (int i =0;i <SNAKE_INITLENGTH; i++ )
	{
		expand_snakelink(x - (SNAKE_INITLENGTH-1)+i, y);
		printxy(x - (SNAKE_INITLENGTH - 1) + i, y, "@");
	}
	

	resolvetick(direction, &length, aimode, 1);
	DWORD lastTickCount = GetTickCount();
	srand(lastTickCount);
	while (1)
	{
		if (!aimode&&_kbhit())
		{
			direction = resolvekeyboard(_getch());
		}	
		
		if (lastTickCount + tickrate < GetTickCount() | aimode)
		{
			
			printxy(0,WINDOW_Y + SPAN_Y + 1," ");
			
			lastTickCount = GetTickCount();

			if (resolvetick(direction,&length,aimode,0))
				return gameover(length);
		}
	}
}
