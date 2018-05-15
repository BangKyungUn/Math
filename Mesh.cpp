#include "stdafx.h"
#include "Mesh.h"


void Mesh::Initialize(Vertex * vert, size_t vertSize, ULONG* indi, size_t indiSize,Material *Mat)
{
	vertices = vert;
	verticesSize = vertSize;
	indices = indi;
	indicesSize = indiSize;
	m_Material = Mat;
	return;
}

void Mesh::Render(ConstantBuffer _ConstantBuffer)
{

	// 셰이더에 메쉬 정보를 넘기기위해 자기자신을 넘김.
	if (m_Material) {
		m_Material->Render(this, _ConstantBuffer);
	}
	return;
}





