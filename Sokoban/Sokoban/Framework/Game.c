#include "stdafx.h"
#include "Game.h"

bool Initialize()
{
	return true;
}

void processInput()
{

}

void update()
{

}

void render()
{

}

int32_t Run()
{
	// Game Loop
	// 게임 루프를 만드는 이유
	// 플레이어로부터의 입력을 하드웨어와 분리시킨다.
	// https://gameprogrammingpatterns.com/game-loop.html

	// Game Loop의 전체를 Frame
	while (true)
	{
		// 1. 입력 처리
		processInput();
		// 2. 업데이트
		update();
		// 3. 렌더링
		render();
	}
}
