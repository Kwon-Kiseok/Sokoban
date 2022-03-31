#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "type.h"

typedef struct Player
{
	int32_t pos_x;	//�÷��̾��� x
	int32_t pos_y;	//�÷��̾��� y
	bool isMoveOnGoal;	//�÷��̾ �� �� �ִ� ������
	EDir direction;	//�÷��̾�� �Էµ� ���� ����

}player;

player* CreatePlayer(int32_t x, int32_t y);
void DeletePlayer(player* player);