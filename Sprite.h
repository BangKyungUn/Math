#pragma once
#include "stdafx.h"
#include "Mesh.h"
#include "Vector.h"
#include "Transform.h"

struct Sprite {
	Mesh *m_Mesh;
	Transform2D trans;
	int Layer;

	void initialize(Mesh* MeshToDraw, int _Layer) {
		m_Mesh = MeshToDraw;
		Layer = _Layer;
	}
	void SetTransforms(Transform2D _trans) {
		trans = _trans;
	}
};