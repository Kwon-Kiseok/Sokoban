#include "stdafx.h"
#include "UI.h"

void gotoXY(int32_t x, int32_t y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void InputSystemUI()
{
	gotoXY(59, 1); printf("SOKOBAN");
	gotoXY(59, 2); printf("       made by. 권기석");
	
	gotoXY(67, 8); printf("↑");
	gotoXY(77, 8); printf("W");
	gotoXY(65, 9); printf("←");
	gotoXY(75, 9); printf("A");
	gotoXY(69, 9); printf("→");
	gotoXY(79, 9); printf("D");
	gotoXY(67, 10); printf("↓");
	gotoXY(77, 10); printf("S");
	gotoXY(67, 9); printf("●");

	gotoXY(65, 12); printf("R : 스테이지 재시작");
	gotoXY(65, 14); printf("ESC : 게임 종료");
}

void GameBoardUI(EStageLevel stageLevel, int32_t goalCount, int32_t boxOnGoalCount)
{
	gotoXY(60, 4); printf("STAGE LEVEL : %d", stageLevel);
	gotoXY(60, 5); printf("진행도 : %d%/%d", boxOnGoalCount, goalCount);
}

void GameOverUI()
{
	gotoXY(26, 18); printf("게임이 종료되었습니다.\n");
}
