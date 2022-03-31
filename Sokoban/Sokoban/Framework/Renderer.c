#include "stdafx.h"
#include "Renderer.h"

#define MAP_SIZE 24

//static char s_backBuffer[MAP_SIZE][MAP_SIZE];

static char s_map[MAP_SIZE][MAP_SIZE] = {
	"*************",
	"*  Sokoban  *",
	"*************"
};

static HANDLE s_consoleHandle;

void clear()
{
	memset(s_map, ' ', sizeof(s_map));
	for (size_t i = 0; i < MAP_SIZE; ++i)
	{
		s_map[i][MAP_SIZE - 1] = '\0';
	}
}

bool InitializeRenderer()
{
	// �ܼ� �ڵ��� ����
	s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == s_consoleHandle)
		return false;

	// ��� ���ŵǰ� �ִ� Ŀ���� ����� ������ �ʰ� ����
	/*CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;

	if (false == SetConsoleCursorInfo(s_consoleHandle, &info))
	{
		return false;
	}*/

	return true;
}

void RenderMap()
{
	const static COORD initialPos = { 0,0 };
	const static CONSOLE_CURSOR_INFO info = { 100, false };
	
	SetConsoleCursorPosition(s_consoleHandle, initialPos);
	// Init���� ������ �� �ܼ� â�� ���ϰų� ��ȭ�� �����
	// �ٽ� �������� �����⿡ ���� ���� ������ �ʱⰪ���� ������
	SetConsoleCursorInfo(s_consoleHandle, &info);

	// ���� �� �׾ ������ �߻� �ϴ� ���� �����ϱ� ����
	// ���� ���۸��� ���� �ϳ��� �����ִ� ��, �ϳ��� ���������� ��
	//memcpy(s_map, s_backBuffer, sizeof(s_map));

	// Sleep �Լ� ����� �����ؾ� �ϴ� ����
	// �����尡 ������� -> ���α׷��� ����
	// ���ӿ����� ���α׷��� ���ߴ� ���� ����� ��
	// ���� �����ִ� ����� ��� �����ִ� ���� �� �����

	//sprintf_s(s_map[0], sizeof(s_map[0]), "DeltaTime : %f", GetDeltaTime());
	//// 1 : deltaTime = x : 1  -> x = 1 / deltaTime
	//int32_t fps = (int32_t)(1 / GetDeltaTime());
	//sprintf_s(s_map[1], sizeof(s_map[1]), "FPS : %d", fps);
	//for (size_t i = 0; i < MAP_SIZE; ++i)
	//{
	//	puts(s_map[i]);
	//}

	// ��� �� ���� �������� ������
	clear();
}

void SetKeyMessage(int32_t keyCode)
{
	sprintf_s(s_map[0], sizeof(s_map[0]), "%cŰ�� ����", keyCode);
}

void SetMessage(const char* message)
{
	strcpy_s(s_map[0], sizeof(s_map[0]), message);
	//sprintf_s(s_map[0], sizeof(s_map[0]), "%s", message);
}
