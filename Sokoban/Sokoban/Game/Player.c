#include "stdafx.h"
#include "Player.h"

player* CreatePlayer(int32_t x, int32_t y)
{
	player* rPlayer = (player*)malloc(sizeof(player));
	
	if (NULL == rPlayer)
	{
		return -1;
	}
	rPlayer->pos_x = x;
	rPlayer->pos_y = y;
	rPlayer->isMoveOnGoal = false;

	return rPlayer;
}

void DeletePlayer(player* player)
{
	free(player);
}