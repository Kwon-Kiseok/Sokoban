#pragma once

#include <stdbool.h>

/// <summary>
/// �������� �ʱ�ȭ�Ѵ�.
/// </summary>
/// <returns>���� true, ���� false</returns>
bool InitializeRenderer();

/// <summary>
/// ���� �׸���
/// </summary>
/// <returns></returns>
void RenderMap();

void SetKeyMessage(int32_t keyCode);

void SetMessage(const char* message);