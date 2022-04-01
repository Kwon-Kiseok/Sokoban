#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef enum KeyCode
{
    KEYCODE_W = 'W',
    KEYCODE_A = 'A',
    KEYCODE_S = 'S',
    KEYCODE_D = 'D',
    KEYCODE_R = 'R',
    KEYCODE_ESC = ESC
} EKeyCode;

void UpdateInput();
bool GetButtonDown(EKeyCode keyCode);
bool GetButtonUp(EKeyCode keyCode);
bool GetButton(EKeyCode keyCode);