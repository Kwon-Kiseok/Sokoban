#include "stdafx.h"
#include "Game.h"
#include "Renderer.h"
#include "Input.h"
#include "Timer.h"

bool Initialize()
{
	if (false == InitializeRenderer())
		return false;

	InitailizeTimer();
	
	return true;
}

void processInput()
{
	UpdateInput();
}

void update()
{
	// 2초 간격으로 특정 메시지를 깜빡이기
	static float diffTime = 0.f;
	static bool canShowMessage = false;

	if (diffTime > 2.0f)
	{
		diffTime = 0.f;
		canShowMessage = !canShowMessage;
	}

	if (canShowMessage)
	{
		SetMessage("twinkle");
	}

	diffTime += GetDeltaTime();
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
		// 프레임 시작 ----- 다음 프레임 시작
		UpdateTimer();
		// 1. 입력 처리
		processInput();
		// 2. 업데이트
		update();
		// 3. 렌더링
		render();
	}

	return 0;
}
