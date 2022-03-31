#include "stdafx.h"
#include "Renderer.h"

static char s_map[MAP_SIZE][MAP_SIZE];
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
    s_consoleHandle = GetStdHandle
    (STD_OUTPUT_HANDLE);

    if (INVALID_HANDLE_VALUE == s_consoleHandle)
    {
        return false;
    }

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

    /*sprintf_s(s_map[0], sizeof(s_map[0]), "DeltaTime : %f", GetDeltaTime());
    */

    /*int32_t fps = 1 / GetDeltaTime();
    sprintf_s(s_map[1], sizeof(s_map[1]), "FPS : %d", fps);*/
    // 1 : deltaTime(�ʴ���) = x : 1
    // x = 1 / deltaTime

    for (size_t i = 0; i < MAP_SIZE; ++i)
    {
        puts(s_map[i]);
    }

    // ��� �Ŀ� ���� �������� ����.
    clear();
}

void SetMessage(const char* message)
{
    strcpy_s(s_map[0], MAP_SIZE, message);
}