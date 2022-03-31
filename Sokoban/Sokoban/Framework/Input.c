#include "stdafx.h"
#include "Input.h"

// 모든 키 입력들을 매번 검수하는 것이 아닌
// 배열의 인덱스에 의미를 부여하여 효율적으로 관리할 수 있다.
static bool s_currentKeyStates[256] = { false };
static bool s_prevKeyStates[256] = { false };

bool isKeyDown(int32_t keyCode)
{
    if (0x8000 & GetAsyncKeyState(keyCode))
        return true;
    else
        return false;
}
void UpdateInput()
{
    memcpy(s_prevKeyStates, s_currentKeyStates, sizeof(s_prevKeyStates));

    for (int32_t keyCode = 0; keyCode < 255; ++keyCode)
    {
        if (isKeyDown(keyCode))
        {
            s_currentKeyStates[keyCode] = true;
        }
        else
        {
            s_currentKeyStates[keyCode] = false;
        }

        // 현재 키의 상태 값을 반환한다.
        // 0x8000(16) => 0b 1000 0000 0000 0000(2) -> 눌린 상태
        // 0x8001(16) => 0b 1000 0000 0000 0001(2) -> 계속 눌린 상태
        // 0x0001(16) => 사이엔 눌렸는데 지금은 뗌
        // 0x0000(16) => 안 눌림
        // 1. 현재 키가 눌렸는지 -> MSB가 set(1)
        // 2. 현재 키가 떼졌는지 -> MSB가 0
        // 3. GetAsyncKeyState() ---- GetAsyncKeyState()
        //                        사이에 눌렸는지 LSB set
        GetAsyncKeyState(keyCode);
    }
}

bool GetButtonDown(EKeyCode keyCode)
{
    if (false == s_prevKeyStates[keyCode] && s_currentKeyStates[keyCode])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GetButtonUp(EKeyCode keyCode)
{
    if (s_prevKeyStates[keyCode] && false == s_currentKeyStates[keyCode])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool GetButton(EKeyCode keyCode)
{
    if (s_prevKeyStates[keyCode] && s_currentKeyStates[keyCode])
    {
        return true;
    }
    else
    {
        return false;
    }
}