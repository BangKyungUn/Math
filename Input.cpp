#include "stdafx.h"
#include "Input.h"


Input::Input()
{
}


Input::~Input()
{
}



float Input::CalcOffset()
{
	static float offset = 0.0f;
	if (GetAsyncKeyState(VK_LEFT)) offset -= 1.0f;
	if (GetAsyncKeyState(VK_RIGHT)) offset += 1.0f;
	return offset;
}

float Input::CalcAngle()
{
	static float angle = 0.0f;
	if (GetAsyncKeyState(VK_UP)) angle += 1.0f;
	if (GetAsyncKeyState(VK_DOWN)) angle -= 1.0f;
	return angle;
}

float Input::CalcScale()
{
	static float scale = 1.0f;
	if (GetAsyncKeyState(VK_PRIOR)) scale *= 1.01f;
	if (GetAsyncKeyState(VK_NEXT)) scale *= 0.99f;
	return scale;
}

float Input::CalcCamera()
{
	static Vector2 cameraLocaton(0.0f, 0.0f);
	static float cameraRotation(0.0f);
	return 0.0f;
}
