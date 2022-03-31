#include "stdafx.h"
#include "Game.h"
#include "Renderer.h"
#include "Input.h"

bool Initialize()
{
	if (false == InitializeRenderer())
		return false;

	return true;
}

void processInput()
{
	UpdateInput();
}

void update()
{
	if (GetButton(KEYCODE_W))
	{
		SetKeyMessage(KEYCODE_W);
	}
	else if (GetButton(KEYCODE_A))
	{
		SetKeyMessage(KEYCODE_A);
	}
	else if (GetButton(KEYCODE_S))
	{
		SetKeyMessage(KEYCODE_S);
	}
	else if (GetButton(KEYCODE_D))
	{
		SetKeyMessage(KEYCODE_D);
	}
}

void render()
{
	RenderMap();
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

	return 0;
}
