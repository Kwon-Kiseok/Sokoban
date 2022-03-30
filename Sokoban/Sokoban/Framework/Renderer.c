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

bool InitializeRenderer()
{
	// 콘솔 핸들을 얻어옴
	s_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (INVALID_HANDLE_VALUE == s_consoleHandle)
		return false;

	// 계속 갱신되고 있는 커서의 모습을 보이지 않게 해줌
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
	// Init에서 해줬을 때 콘솔 창이 변하거나 변화가 생기면
	// 다시 포지션이 깨졌기에 렌더 해줄 때마다 초기값으로 설정함
	SetConsoleCursorInfo(s_consoleHandle, &info);

	// 렌더 시 테어링 현상이 발생 하는 것을 방지하기 위해
	// 더블 버퍼링을 통해 하나는 보여주는 용, 하나는 렌더용으로 둠
	//memcpy(s_map, s_backBuffer, sizeof(s_map));

	// Sleep 함수 사용을 기피해야 하는 이유
	// 쓰레드가 멈춰버림 -> 프로그램이 멈춤
	// 게임에서는 프로그램이 멈추는 일은 없어야 함
	// 차라리 멈춰있는 장면을 계속 보여주는 것이 더 권장됨

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		puts(s_map[i]);
	}
}
