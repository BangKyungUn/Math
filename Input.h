#pragma once
#include "Vector.h"
class Input
{
public:
	Input();
	~Input();

	// �Ű����� �޾Ƽ� �ϴ°ɷ� ���� �Ű�����Ÿ���� ����� �ؾߵ����� ���� �����غ����� ����Ʈ
	static float CalcOffset();
	float CalcAngle();
	float CalcScale();
	// �׷��� ���⼭ ī�޶� �����Ҷ� ȣ��
	float CalcCamera();
	
	
};

