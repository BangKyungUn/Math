
#include "stdafx.h"
#include "Vector.h"


float Vector2D::Dist(const Vector2D &V1, const Vector2D &V2) {
	return sqrtf(Vector2D::DistSquared(V1, V2));
}

float Vector2D::DistSquared(const Vector2D &V1, const Vector2D &V2) {
	return (V2.x - V1.x) * (V2.x - V1.x) + (V2.y - V1.y) * (V2.y - V1.y);
}