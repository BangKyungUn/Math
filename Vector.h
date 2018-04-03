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


	FORCEINLINE Vector2D operator *(const Matrix2 Mat) const;
	FORCEINLINE float operator|(const Vector2D& v) const;
	FORCEINLINE float operator^ (const Vector2D& v) const;
	FORCEINLINE bool Equals(const Vector2D& V, float Tolerance = KINDA_SMALL_NUMBER) const;
	FORCEINLINE Vector2D operator+(const Vector2D &v);
	FORCEINLINE Vector2D operator-(const Vector2D &v);
	FORCEINLINE Vector2D operator*(const float &Scale) const;
	FORCEINLINE Vector2D operator/(const float &Scale) const;

	FORCEINLINE Vector2D operator+=(const Vector2D &v);
	FORCEINLINE Vector2D operator-=(const Vector2D &v);
	FORCEINLINE Vector2D operator*=(const float &Scale);
	FORCEINLINE Vector2D operator/=(const float &Scale);
};

FORCEINLINE bool Vector2D::Equals(const Vector2D&v, float Tolerance) const
{
	return fabs(x - v.x) <= Tolerance && fabs(y - v.y) <= Tolerance;
}

FORCEINLINE Vector2D Vector2D::operator+(const Vector2D & v)
{
	return Vector2D(x + v.x, y + v.y);
}

FORCEINLINE Vector2D Vector2D::operator-(const Vector2D & v)
{
	return Vector2D(x - v.x, y - v.y);
}

FORCEINLINE Vector2D Vector2D::operator*(const float & Scale) const
{
	return Vector2D(x * Scale,y*Scale);
}

FORCEINLINE Vector2D Vector2D::operator/(const float & Scale) const
{
	return Vector2D(x / Scale, y / Scale);
}

FORCEINLINE Vector2D Vector2D::operator+=(const Vector2D & v)
{
	x += v.x;
	y += v.y;
	return *this;
}

FORCEINLINE Vector2D Vector2D::operator-=(const Vector2D & v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

FORCEINLINE Vector2D Vector2D::operator*=(const float & Scale)
{
	x *= Scale;
	y *= Scale;
	return *this;
}

FORCEINLINE Vector2D Vector2D::operator/=(const float & Scale)
{
	x /= Scale;
	y /= Scale;
	return *this;
}

FORCEINLINE float Vector2D::operator|(const Vector2D& v) const
{
	return x * v.x + y + v.y;
}

FORCEINLINE float Vector2D::operator^(const Vector2D& v) const
{
	return  x * v.y - y * v.x;
}