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
    SetConsoleCursorInfo(s_consoleHandle, &info);

    const char** stage = GetMap();
    memcpy(s_map, stage, sizeof(s_map));

    for (size_t i = 0; i < MAP_SIZE; ++i)
    {
        puts(s_map[i]);
    }

    clear();
}

//void SetMessage(const char* message)
//{
//    strcpy_s(s_map[0], MAP_SIZE, message);
//}