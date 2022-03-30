#pragma once

#include <stdbool.h>

/// <summary>
/// 렌더러를 초기화한다.
/// </summary>
/// <returns>성공 true, 실패 false</returns>
bool InitializeRenderer();

/// <summary>
/// 맵을 그린다
/// </summary>
/// <returns></returns>
void RenderMap();