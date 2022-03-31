#pragma once

// 역할
// 1. 스테이지를 불러옴
// 2. 스테이지 현재 상황을 보관
// 3. 스테이지가 클리어 됐는지

typedef enum MapType
{
	MAPTYPE_WALL = '#',
	MAPTYPE_PLAYER = 'P',
	MAPTYPE_BOX = 'B',
	MAPTYPE_GOAL = 'O',
	MAPTYPE_BOX_ON_GOAL = '@',
	MAPTYPE_PATH = ' '
}EMapType;

typedef enum StageLevel
{
	STAGE_01 = 1, 
	STAGE_MAX 
}EStageLevel;

void LoadStage(EStageLevel level);

void UpdateStage();

const char** GetMap();

bool CheckPosition(int32_t i, int32_t j);