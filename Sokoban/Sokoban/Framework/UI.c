#include "stdafx.h"
#include "UI.h"

void gotoXY(int32_t x, int32_t y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void UI()
{
	gotoXY(59, 1); printf("SOKOBAN");
	gotoXY(59, 2); printf("       made by. �Ǳ⼮");
	gotoXY(67, 8); printf("��");
	gotoXY(77, 8); printf("W");
	gotoXY(65, 9); printf("��");
	gotoXY(75, 9); printf("A");
	gotoXY(69, 9); printf("��");
	gotoXY(79, 9); printf("D");
	gotoXY(67, 10); printf("��");
	gotoXY(77, 10); printf("S");
	gotoXY(67, 9); printf("��");
}
