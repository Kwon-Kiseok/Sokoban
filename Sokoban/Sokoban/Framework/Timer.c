#include "stdafx.h"
#include "Timer.h"

static clock_t s_prevTick;
static float s_deltaTime;

void InitailizeTimer()
{
	s_prevTick = clock();
}

void UpdateTimer()
{
	clock_t currentTick = clock();

	s_deltaTime = (currentTick - s_prevTick)/ (float)CLOCKS_PER_SEC;
	
	s_prevTick = currentTick;
}

float GetDeltaTime()
{
	return s_deltaTime;
}
