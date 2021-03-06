#pragma once
#include <stdint.h>

void gotoXY(int32_t x, int32_t y);
void InputSystemUI();
void GameOverUI();
void GameBoardUI(EStageLevel stageLevel, int32_t goalCount, int32_t boxOnGoalCount);