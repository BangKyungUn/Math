#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "Vector.h"


struct Sprite {
	Mesh *m_Mesh;
	Vector3 pos;
	Vector3 rot;
	float Scale;
	int Layer;

	void initialize(Mesh* MeshToDraw, Vector3 _pos, Vector3 _rot, float _Scale, int _Layer) {
		m_Mesh = MeshToDraw;
		pos = _pos;
		rot = _rot;
		Scale = _Scale;
		Layer = _Layer;
	}
};