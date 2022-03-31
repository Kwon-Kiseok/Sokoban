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
	// 2�� �������� Ư�� �޽����� �����̱�
	static float diffTime = 0.f;
	static bool canShowMessage = false;

	diffTime += GetDeltaTime();

	if (diffTime > 0.5f)
	{
		diffTime = 0.f;
		canShowMessage = !canShowMessage;
	}

	if (canShowMessage)
	{
		SetMessage("twinkle");
	}

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
