#pragma once
#include"varable.h"

int mainmenu()
{
	static char* overt = "\t\t         `..------.`          \n\t\t      `.:////////////-`       \n\t\t    .oh+-:.``   ``.--/ys-     \n\t\t   -yhho.    ``.    `+hhh/    \n\t\t  `yhh+     `s`s.     :hhh-   \n\t\t  :hhh`    `oh`yy.     shho   \n\t\t  :hhh`  `/yhh`yhy+.   shho   \n\t\t  `yhh+.+yhhs: -ohhho-:hhh-   \n\t\t   -hhhhhhs-`    .ohhhhhh/    \n\t\t    .shhhy/.`   `.:shhhy:     \n\t\t      -oyhhhhyyyyhhhho:`      \n\t\t         .:+ooooo+/-`         \n\t\t";
	
	gotoxy(0,0);
	printf("%s",overt);
	printf("\n\t\t\t����� ������ũ");
	gotoxy(10, 15);
	printf("�����ϱ�");
	gotoxy(25, 15);
	printf("���Ͱ� �ϱ�");
	gotoxy(45,15);
	printf("�����ϱ�");
	gotoxy(10, 19);
	printf("was(x)d�� �������� �޴��� �����ϼ���");


	int selection=0;
	char input;
	gotoxy(8, 15);
	printf("��");
	gotoxy(WINDOW_CORNER);

	while (1)
	{
		input = _getche();
		
		switch (input)
		{
		case 's':case 'x':case 'd':
			selection++;
			break;
		case 'w':case 'a':
			selection--;
			break;
		case '\r':
			system("cls");
			switch (selection)
			{
			case 0:
				return STATE_GAME;
			case 1:
				return STATE_GAME_AI;
			case 2:
				return STATE_GAME_EXIT;
			default:
				return STATE_MENU;
			}
		}
		selection += 3;
		selection %= 3;

		gotoxy(8, 15); printf("  ");
		gotoxy(23, 15); printf("  ");
		gotoxy(43, 15); printf("  ");

		switch (selection)
		{
		case 0:
			gotoxy(8, 15); printf("��"); break;
		case 1:
			gotoxy(23, 15); printf("��"); break;
		case 2:
			gotoxy(43, 15); printf("��");
		}
		gotoxy(WINDOW_CORNER);
	}
}