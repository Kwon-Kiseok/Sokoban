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
	STAGE_MAX 
}EStageLevel;

void LoadStage(EStageLevel level);

void UpdateStage();

const char** GetMap();

bool CheckPosition(int32_t i, int32_t j);