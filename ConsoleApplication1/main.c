#include<stdio.h>
#include<windows.h>
#include<conio.h>

#include"game.h"
#include"snakelink.h"
#include"mainmenu.h"

#define TOLINK(X) (*linksnake)(X)




int main(void)
{

	int status = 0;

	while (1)//game loop
	{
		system("cls");
		switch (status)
		{
		case STATE_MENU:
			status = mainmenu();
			break;
		case STATE_GAME:
			status = gameloop(0);
			break;
		case STATE_GAME_AI:
			status = gameloop(1);//aigameloop(); break;
			break;
		case STATE_NEW_GAME_AI:
			status = gameloop(2);
			break;
		case STATE_GAME_EXIT:
			return;
		default:
			status = 0;
		}

	}
}