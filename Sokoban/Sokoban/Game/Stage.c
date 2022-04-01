#include "stdafx.h"
#include "Stage.h"

static char s_map[MAP_SIZE][MAP_SIZE];
static int32_t s_goalCount = 0; // 목표 갯수
static int32_t s_boxOnGoalCount = 0; // 현재 맞은 개수
static int32_t s_playerX = 0;
static int32_t s_playerY = 0;
static EStageLevel s_stageLevel = 1;
static player* s_player = NULL;

bool parseMapType(int32_t i, int32_t j, char mapType)
{
	switch (mapType)
	{
		// 각 맵 타일별로 해줘야 하는 일들
	case MAPTYPE_PLAYER:
	{
		s_player = CreatePlayer(j, i);
	}
		return true;
	case MAPTYPE_WALL:
		return true;
	case MAPTYPE_BOX:
		return true;
	case MAPTYPE_GOAL:
		s_goalCount++;
		return true;
	case MAPTYPE_BOX_ON_GOAL:
		return true;
	case MAPTYPE_PATH:
		return true;
	default:
		return false;
	}
	// 반환은 행에 다다랐을 때
}

bool BoxMove(EDir input_dir)
{
	int32_t boxX = s_player->pos_x;
	int32_t boxY = s_player->pos_y;

	switch (input_dir)
	{
	case DIR_UP:
		boxY--;
		break;
	case DIR_LEFT:
		boxX--;
		break;
	case DIR_DOWN:
		boxY++;
		break;
	case DIR_RIGHT:
		boxX++;
		break;
	}

	if (s_map[boxY][boxX] == MAPTYPE_PATH || s_map[boxY][boxX] == MAPTYPE_BOX_ON_GOAL)
	{
		s_map[boxY][boxX] = 'B';
		return true;
	}
	else if (s_map[boxY][boxX] == MAPTYPE_GOAL)
	{
		s_map[boxY][boxX] = '@';
		s_boxOnGoalCount++;
		return true;
	}
	else
		return false;
}

bool CanMove(int32_t i, int32_t j, EDir input_dir)
{
	char** curPos = s_map[s_player->pos_y][s_player->pos_x];
	// 현재 이동한 곳이 벽일 경우
	if (curPos == MAPTYPE_WALL)
	{
		return false;
	}
	// 현재 이동한 곳이 박스일 경우
	else if (curPos == MAPTYPE_BOX)
	{
		// 박스 이동
		if (!BoxMove(input_dir))
			return false;
	}
	// 현재 이동한 곳이 골일 경우
	else if (curPos == MAPTYPE_GOAL)
	{
		// 위에 올라갈 순 있음, 단 지나온 다음 다시 'O'로 바꿔줘야함
		s_player->isMoveOnGoal = true;
		return true;
	}
	// 현재 이동한 곳이 BoxOnGoal일 경우
	else if (curPos == MAPTYPE_BOX_ON_GOAL)
	{
		s_player->isMoveOnGoal = true;
		s_boxOnGoalCount--;
		// 박스 이동
		if (!BoxMove(input_dir))
			return false;
		return true;
	}
	s_player->isMoveOnGoal = false;
	return true;
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

bool isStageClear()
{
	if (s_goalCount == s_boxOnGoalCount)
	{
		s_stageLevel++;
		return true;
	}
	return false;
}

void LoadStage(EStageLevel level)
{
	assert(STAGE_01 <= level && level <= STAGE_MAX);

	static char path[MAX_PATH] = { 0 };

	sprintf_s(path, sizeof(path), "Stage/Stage%02d.txt",
		(int32_t)level);
	FILE* fp = NULL;
	fopen_s(&fp, path, "r");
	assert(fp != NULL);

	clearStage();

	for (int32_t i = 0; i < MAP_SIZE; ++i)
	{
		for (int32_t j = 0; j < MAP_SIZE; ++j)
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
	if (!s_player->isMoveOnGoal)
		s_map[s_player->pos_y][s_player->pos_x] = ' ';
	// 원래 있던 곳이 Goal일 경우 'O'로 돌려줌
	else
		s_map[s_player->pos_y][s_player->pos_x] = 'O';

	if (GetButtonUp(KEYCODE_W))
	{
		s_player->pos_y--;
		if (!CanMove(s_player->pos_y, s_player->pos_x, DIR_UP))
		{
			s_player->pos_y++;
		}
	}
	else if (GetButtonUp(KEYCODE_A))
	{
		s_player->pos_x--;
		if (!CanMove(s_player->pos_y, s_player->pos_x, DIR_LEFT))
		{
			s_player->pos_x++;
		}
	}
	else if (GetButtonUp(KEYCODE_S))
	{
		s_player->pos_y++;
		if (!CanMove(s_player->pos_y, s_player->pos_x, DIR_DOWN))
		{
			s_player->pos_y--;
		}
	}
	else if (GetButtonUp(KEYCODE_D))
	{
		s_player->pos_x++;
		if (!CanMove(s_player->pos_y, s_player->pos_x, DIR_RIGHT))
		{
			s_player->pos_x--;
		}
	}
	// 새로 도착한 곳에 그려줌
	s_map[s_player->pos_y][s_player->pos_x] = 'P';
}

void PlayerInput()
{

	// 스테이지 리셋 버튼
	if (GetButtonUp(KEYCODE_R))
	{
		LoadStage(s_stageLevel);
	}
	// 플레이어 이동
	PlayerMove();
}

void UpdateStage()
{
	// 입력에 대해서 처리를 함
	PlayerInput();
	// 게임이 클리어 됐는지도 파악함
	if (isStageClear())
	{
		DeletePlayer(s_player);
		if (s_stageLevel != STAGE_MAX)
		{
			LoadStage(s_stageLevel);
		}
		else
		{
			GameOver();
		}
	}

}

const char** GetMap()
{
	return (char**)s_map;
}

void GameOver()
{
	system("cls");
	puts("-   게임 클리어   -");
	exit(1);
}

// 소코반 게임 완성
// 1. @에서 밀면 박스 체크를 다시 해줘야 함
// 연출 추가
// 컨텐츠 추가(함정 같은거)