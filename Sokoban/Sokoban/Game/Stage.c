#include "stdafx.h"
#include "Stage.h"

typedef struct tagStage
{
	char Map[MAP_SIZE][MAP_SIZE];
}Stage;

void LoadStage(EStageLevel level)
{
	assert(STAGE_01 <= level && level < STAGE_MAX);
}
