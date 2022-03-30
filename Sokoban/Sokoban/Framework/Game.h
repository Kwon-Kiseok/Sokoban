#pragma once

#include <stdint.h>
#include <stdbool.h>

///<summary>
/// 게임과 관련된 데이터를 초기화 한다.
///</summary>
/// <returns>정상적으로 초기화 - true, 비정상 - false</returns>
bool Initialize();

///<summary>
/// 게임을 동작시킨다.
///</summary>
/// <returns>정상적으로 종료 됐다면 0</returns>
int32_t Run();