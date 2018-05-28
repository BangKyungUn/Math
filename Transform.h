#pragma once
#include "Vector.h"


// Sprite안에 트랜스폼 넣기
struct Transform2D
{
public:
	Transform2D() {}
	~Transform2D() {}
	Transform2D(Vector2 _Loc, float _Rot, float _Scale) : Location(_Loc), Rotation(_Rot), Scale(_Scale) {}


	Matrix3 GetTRSMatrix() {
		Matrix3 TMat, RMat, SMat;
		TMat.SetTranslation(Location.X, Location.Y);
		RMat.SetRotation(Rotation);
		SMat.SetScale(Scale);
		return TMat * RMat * SMat;
	}

	Matrix3 GetViewMatrix()
	{
		Matrix3 TMat, RMat;
		TMat.SetTranslation(-Location.X, -Location.Y);
		RMat.SetRotation(Rotation);
		RMat.Tranpose();
		return RMat * TMat;
	}
public:
	Vector2 Location;
	float Rotation;
	float Scale;

};