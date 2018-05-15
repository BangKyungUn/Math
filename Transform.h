#pragma once
#include "Vector.h"


// Sprite안에 트랜스폼 넣기
struct Transform2D
{
public:
	Transform2D() {}
	~Transform2D() {}
	Transform2D(Vector2 _Loc, float _Rot, Vector2 _Scale) : Location(_Loc), Rotation(_Rot), Scale(_Scale) {}


	Matrix3 GetTRSMatrix() {
		Matrix3 TransMat, RotMat, ScaleMat;
		TransMat.SetTranslation(Location.X, Location.Y);
		RotMat.SetRotation(Rotation);
		ScaleMat.SetScale(Scale.X);
		return TransMat * RotMat * ScaleMat;
	}
public:
	Vector2 Location;
	float Rotation;
	Vector2 Scale;

};