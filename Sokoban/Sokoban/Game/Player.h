#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "type.h"

typedef struct Player
{
	int32_t pos_x;	//플레이어의 x
	int32_t pos_y;	//플레이어의 y
	bool isMoveOnGoal;	//플레이어가 갈 수 있는 곳인지
	EDir direction;	//플레이어에게 입력된 현재 방향

}player;

player* CreatePlayer(int32_t x, int32_t y);
void DeletePlayer(player* player);