
#include "stdafx.h"
#include "Vector.h"


float Vector2D::Dist(const Vector2D &V1, const Vector2D &V2) {
	return sqrtf(Vector2D::DistSquared(V1, V2));
}

float Vector2D::DistSquared(const Vector2D &V1, const Vector2D &V2) {
	return (V2.x - V1.x) * (V2.x - V1.x) + (V2.y - V1.y) * (V2.y - V1.y);
}

Vector2D Vector2D::operator*(const Matrix2 Mat) const
{
	Vector2D Result; // (0,1) // 2행 1렬 짜리 매트릭스가 들어와야함.

	Result.x = x * Mat._11 + y * Mat._21;
	Result.y = x * Mat._21 + y * Mat._22;

	return Result;
}
