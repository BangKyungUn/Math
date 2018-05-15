#pragma once
#include "Vector.h"
class Input
{
public:
	Input();
	~Input();

	// 매개변수 받아서 하는걸로 변경 매개변수타입을 오토로 해야될지도 추후 생각해봐야할 포인트
	static float CalcOffset();
	float CalcAngle();
	float CalcScale();
	// 그래서 여기서 카메라 연산할때 호출
	float CalcCamera();
	
	
};

