#include "stdafx.h"
#include "Stage.h"

static char s_map[MAP_SIZE][MAP_SIZE];
static int32_t s_goalCount = 0; // ��ǥ ����
static int32_t s_boxOnGoalCount = 0; // ���� ���� ����
static int32_t s_boxCount = 0; // �ڽ� ����
static int32_t s_playerX = 0;
static int32_t s_playerY = 0;


bool parseMapType(int32_t i, int32_t j, char mapType)
{
	switch (mapType)
	{
		// �� �� Ÿ�Ϻ��� ����� �ϴ� �ϵ�
	case MAPTYPE_PLAYER:
	{
		s_playerX = j;
		s_playerY = i;
	}
		return true;
	case MAPTYPE_WALL:
		// �̵��Ұ� -> ���� �÷��̾��� ��ġ = -�Է°�
		return true;
	case MAPTYPE_BOX:
		s_boxCount++;
		// �ڽ��� ���� �Է��� �������� ĳ���͸� �̵�, �ڽ��� ��
		// �� �ڽ� �տ� ���� �ִٸ� �и����ʰ� ĳ���͵� �̵����� ����
		return true;
	case MAPTYPE_GOAL:
		s_goalCount++;
		// �ڽ��� �а��ִ� ä�� �ö�´ٸ� -> BOX_ON_GOAL�� ����
		// �׳� �������ٸ� ����
		return true;
	case MAPTYPE_BOX_ON_GOAL:
		s_boxOnGoalCount++;
		// �̵��Ұ� + ���� ȹ��
		return true;
	case MAPTYPE_PATH:
		return true;
	default:
		return false;
	}
	// ��ȯ�� �࿡ �ٴٶ��� ��
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
	// ���� �ִ� �� �Ҹ�
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

	// ���� ������ ���� �׷���
	s_map[s_playerY][s_playerX] = 'P';
}

bool CheckPosition(int32_t i, int32_t j)
{
	// ���� �̵��� ���� ���� ���
	if (s_map[s_playerY][s_playerX] == MAPTYPE_WALL)
	{
		return false;
	}
	return true;
}

void UpdateStage()
{
	// �Է¿� ���ؼ� ó���� ��
	PlayerMove();
	// ������ Ŭ���� �ƴ����� �ľ���
}

const char** GetMap()
{
	return s_map;
}

// ���ڹ� ���� �ϼ�
// �������� ���� �� �߰�
// ���� �߰�
// ������ �߰�(���� ������)