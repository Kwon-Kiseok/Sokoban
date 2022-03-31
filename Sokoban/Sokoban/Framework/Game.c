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
	
	LoadStage(STAGE_01);

	return true;
}

void processInput()
{
	UpdateInput();
}

void update()
{
	UpdateStage();
}

void render()
{
	RenderMap();
}

int32_t Run()
{
	// Game Loop
	// ���� ������ ����� ����
	// �÷��̾�κ����� �Է��� �ϵ����� �и���Ų��.
	// https://gameprogrammingpatterns.com/game-loop.html

	// Game Loop�� ��ü�� Frame
	while (true)
	{
		// ������ ���� ----- ���� ������ ����
		UpdateTimer();
		// 1. �Է� ó��
		processInput();
		// 2. ������Ʈ
		update();
		// 3. ������
		render();
	}

	return 0;
}
