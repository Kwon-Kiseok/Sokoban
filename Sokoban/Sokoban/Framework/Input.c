#include "stdafx.h"
#include "Input.h"

// ��� Ű �Էµ��� �Ź� �˼��ϴ� ���� �ƴ�
// �迭�� �ε����� �ǹ̸� �ο��Ͽ� ȿ�������� ������ �� �ִ�.
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

        // ���� Ű�� ���� ���� ��ȯ�Ѵ�.
        // 0x8000(16) => 0b 1000 0000 0000 0000(2) -> ���� ����
        // 0x8001(16) => 0b 1000 0000 0000 0001(2) -> ��� ���� ����
        // 0x0001(16) => ���̿� ���ȴµ� ������ ��
        // 0x0000(16) => �� ����
        // 1. ���� Ű�� ���ȴ��� -> MSB�� set(1)
        // 2. ���� Ű�� �������� -> MSB�� 0
        // 3. GetAsyncKeyState() ---- GetAsyncKeyState()
        //                        ���̿� ���ȴ��� LSB set
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