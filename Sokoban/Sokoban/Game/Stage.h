#pragma once

// ����
// 1. ���������� �ҷ���
// 2. �������� ���� ��Ȳ�� ����
// 3. ���������� Ŭ���� �ƴ���

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

void GameOver();