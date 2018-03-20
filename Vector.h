#pragma once

#include "stdafx.h"
#include "Matrix.h"


struct Vector2D {

public :
	float x;
	float y;

public:
	Vector2D() : x(0), y(0) {}
	Vector2D(float inX , float inY) : x(inX) , y(inY) {}

	static float Dist(const Vector2D &V1, const Vector2D &V2);
	static float DistSquared(const Vector2D &V1, const Vector2D &V2);


	Vector2D operator *(const Matrix2 Mat) const;
};
