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
	STAGE_02,
	STAGE_03,
	STAGE_04,
	STAGE_05,
	STAGE_06,
	STAGE_07,
	STAGE_08,
	STAGE_09,
	STAGE_MAX 
}EStageLevel;

typedef struct BOX
{
	int32_t pos_x;
	int32_t pos_y;
	bool isCanMove;
};

void LoadStage(EStageLevel level);

void UpdateStage();

const char** GetMap();

void clearStage();

void GameClear();

void GameOver();

bool parseMapType(int32_t i, int32_t j, char mapType);
bool isStageClear();
void PlayerMove();
void PlayerInput();