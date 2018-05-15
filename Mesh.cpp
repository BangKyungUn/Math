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

	// ���̴��� �޽� ������ �ѱ������ �ڱ��ڽ��� �ѱ�.
	if (m_Material) {
		m_Material->Render(this, _ConstantBuffer);
	}
	return;
}





