#include "stdafx.h"
#include "Stage.h"

static char s_map[MAP_SIZE][MAP_SIZE];
static int32_t s_goalCount = 0; // ��ǥ ����
static int32_t s_boxOnGoalCount = 0; // ���� ���� ����
static int32_t s_playerX = 0;
static int32_t s_playerY = 0;
static EStageLevel s_stageLevel = 1;
static player* s_player;

bool parseMapType(int32_t i, int32_t j, char mapType)
{
	switch (mapType)
	{
		// �� �� Ÿ�Ϻ��� ����� �ϴ� �ϵ�
	case MAPTYPE_PLAYER:
	{
		//s_playerX = j;
		//s_playerY = i;
		s_player = CreatePlayer(j, i);
	}
		return true;
	case MAPTYPE_WALL:
		// �̵��Ұ� -> ���� �÷��̾��� ��ġ = -�Է°�
		return true;
	case MAPTYPE_BOX:
		// �ڽ��� ���� �Է��� �������� ĳ���͸� �̵�, �ڽ��� ��
		// �� �ڽ� �տ� ���� �ִٸ� �и����ʰ� ĳ���͵� �̵����� ����
		return true;
	case MAPTYPE_GOAL:
		s_goalCount++;
		// �ڽ��� �а��ִ� ä�� �ö�´ٸ� -> BOX_ON_GOAL�� ����
		// �׳� �������ٸ� ����
		return true;
	case MAPTYPE_BOX_ON_GOAL:
		// �̵��Ұ� + ���� ȹ��
		return true;
	case MAPTYPE_PATH:
		return true;
	default:
		return false;
	}
	// ��ȯ�� �࿡ �ٴٶ��� ��
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
	// ���� �̵��� ���� ���� ���
	if (s_map[s_player->pos_y][s_player->pos_x] == MAPTYPE_WALL)
	{
		return false;
	}
	// ���� �̵��� ���� �ڽ��� ���
	else if (s_map[s_player->pos_y][s_player->pos_x] == MAPTYPE_BOX)
	{
		// �ڽ� �̵�
		if (!BoxMove(input_dir))
			return false;
	}
	// ���� �̵��� ���� ���� ���
	// ���� �̵��� ���� BoxOnGoal�� ���

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

void PlayerInput()
{
	// �������� ���� ��ư
	if (GetButtonUp(KEYCODE_R))
	{
		LoadStage(s_stageLevel);
	}

	// ���� �ִ� �� �Ҹ�
	s_map[s_player->pos_y][s_player->pos_x] = ' ';

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

	// ���� ������ ���� �׷���
	s_map[s_player->pos_y][s_player->pos_x] = 'P';
}

void UpdateStage()
{
	// �Է¿� ���ؼ� ó���� ��
	PlayerInput();
	// ������ Ŭ���� �ƴ����� �ľ���
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
	printf("���� Ŭ����");
	exit(1);
}

// ���ڹ� ���� �ϼ�
// �������� ���� �� �߰�
// ���� �߰�
// ������ �߰�(���� ������)