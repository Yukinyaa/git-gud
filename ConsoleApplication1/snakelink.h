#pragma once
#include<stdlib.h>

typedef struct Link linksnake;
typedef struct Link 
{
	int x, y;
	linksnake *next, *prev;
}linksnake;

linksnake *getstart_snakelink(linksnake *start)
{
	static linksnake *saved = LINK_NULL;
	if (start != 0)
	{
		saved = start;
	}
	return saved;
}




linksnake *getend_snakelink(linksnake *end)
{
	static linksnake *saved = LINK_NULL;
	if (end != 0)
	{
		saved = end;
	}
	return saved;
}
linksnake* expand_snakelink(int x, int y)
{
	linksnake *start = getstart_snakelink(0), *next;
	
	next = (linksnake*)malloc(sizeof(linksnake));

	if (start != LINK_NULL) start->next = next;
	else getend_snakelink(next);
	getstart_snakelink(next);

	next->prev = start;
	next->next = LINK_NULL;
	
	next->x = x;
	next->y = y;
	return next;
}
void pop_snakelink()
{
	linksnake *end = getend_snakelink(0);
	if (end == LINK_NULL)
		return;
	if ((*end).next != LINK_NULL) {
		end->next->prev = LINK_NULL;
		getend_snakelink(end->next);
	}
	else {
		getstart_snakelink(LINK_NULL);
	}
	free(end);
}

void flushsnake_(linksnake *lnk)
{
	if (lnk == LINK_NULL)
		return;
	linksnake  *next = lnk->next;
	pop_snakelink();
	flushsnake_(next);
}

void flushsnake()
{
	flushsnake_(getend_snakelink(0));
}
