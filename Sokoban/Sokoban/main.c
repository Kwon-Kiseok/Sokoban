#include "stdafx.h"
#include "Framework/Game.h"

int main()
{
	if (false == Initialize())
	{
		puts("게임을 로딩하는 데 문제가 생겼습니다.");
		return 1;
	}

	return Run();
}