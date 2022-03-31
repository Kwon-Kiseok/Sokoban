#include "stdafx.h"
#include "Stage.h"

static char s_map[MAP_SIZE][MAP_SIZE];
static int32_t s_goalCount = 0; // 목표 갯수
static int32_t s_boxOnGoalCount = 0; // 현재 맞은 개수
static int32_t s_boxCount = 0; // 박스 개수
static int32_t s_playerX = 0;
static int32_t s_playerY = 0;


bool parseMapType(int32_t i, int32_t j, char mapType)
{
	switch (mapType)
	{
		// 각 맵 타일별로 해줘야 하는 일들
	case MAPTYPE_PLAYER:
	{
		s_playerX = j;
		s_playerY = i;
	}
		return true;
	case MAPTYPE_WALL:
		// 이동불가 -> 내가 플레이어의 위치 = -입력값
		return true;
	case MAPTYPE_BOX:
		s_boxCount++;
		// 박스를 내가 입력한 방향으로 캐릭터를 이동, 박스를 밈
		// 단 박스 앞에 벽이 있다면 밀리지않고 캐릭터도 이동하지 않음
		return true;
	case MAPTYPE_GOAL:
		s_goalCount++;
		// 박스를 밀고있는 채로 올라온다면 -> BOX_ON_GOAL로 변경
		// 그냥 지나간다면 무시
		return true;
	case MAPTYPE_BOX_ON_GOAL:
		s_boxOnGoalCount++;
		// 이동불가 + 점수 획득
		return true;
	case MAPTYPE_PATH:
		return true;
	default:
		return false;
	}
	// 반환은 행에 다다랐을 때
}

void clearStage()
{
	memset(s_map, ' ', sizeof(s_map));
	for (size_t i = 0; i < MAP_SIZE; ++i)
	{
		s_map[i][MAP_SIZE - 1] = '\0';
	}
	s_goalCount = 0;
	s_boxOnGoalCount = 0;
	s_playerX = 0;
	s_playerY = 0;
}

void LoadStage(EStageLevel level)
{
	assert(STAGE_01 <= level && level < STAGE_MAX);

	static char path[MAX_PATH] = { 0 };

	sprintf_s(path, sizeof(path), "Stage/Stage%02d.txt",
		(int32_t)level);
	FILE* fp = NULL;
	fopen_s(&fp, path, "r");
	assert(fp != NULL);

	clearStage();

	for (size_t i = 0; i < MAP_SIZE; ++i)
	{
		for (size_t j = 0; j < MAP_SIZE; ++j)
		{
			char ch = fgetc(fp);

			if (false == parseMapType(i, j, ch))
			{
				break;
			}

			s_map[i][j] = ch;
		}

		if (feof(fp))
		{
			break;
		}
	}

	fclose(fp);
}

void PlayerMove()
{
	// 원래 있던 곳 소멸
	s_map[s_playerY][s_playerX] = ' ';

	if (GetButtonUp(KEYCODE_W))
	{
		s_playerY--;
		if (!CheckPosition(s_playerY, s_playerX))
		{
			s_playerY++;
		}
	}
	else if (GetButtonUp(KEYCODE_A))
	{
		s_playerX--;
		if (!CheckPosition(s_playerY, s_playerX))
		{
			s_playerX++;
		}
	}
	else if (GetButtonUp(KEYCODE_S))
	{
		s_playerY++;
		if (!CheckPosition(s_playerY, s_playerX))
		{
			s_playerY--;
		}
	}
	else if (GetButtonUp(KEYCODE_D))
	{
		s_playerX++;
		if (!CheckPosition(s_playerY, s_playerX))
		{
			s_playerX--;
		}
	}

	// 새로 도착한 곳에 그려줌
	s_map[s_playerY][s_playerX] = 'P';
}

bool CheckPosition(int32_t i, int32_t j)
{
	// 현재 이동한 곳이 벽일 경우
	if (s_map[s_playerY][s_playerX] == MAPTYPE_WALL)
	{
		return false;
	}
	return true;
}

void UpdateStage()
{
	// 입력에 대해서 처리를 함
	PlayerMove();
	// 게임이 클리어 됐는지도 파악함
}

const char** GetMap()
{
	return s_map;
}

// 소코반 게임 완성
// 스테이지 여러 개 추가
// 연출 추가
// 컨텐츠 추가(함정 같은거)