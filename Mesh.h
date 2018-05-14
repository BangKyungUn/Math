#pragma once
#include "Vector.h"
#include "Triangle.h"
#include "Texture.h"
#include "GDIHelper.h"
#include "SoftRenderer.h"
#include "Renderer.h"
#include "Material.h" 

class Material;
struct MatrixBuffer;

struct Mesh {
private:
	Vertex* vertices;
	size_t verticesSize;
	ULONG* indices;
	size_t indicesSize;
	Material *m_Material;
public:
	Mesh() {
		vertices = 0;
		verticesSize = 0;
		indices = 0;
		indicesSize = 0;
		m_Material = 0;
	};
	~Mesh() {
		if (vertices) {
			delete vertices;
			vertices = 0;
		}
		if (indices) {
			delete indices;
			indices = 0;
		}
		if (m_Material) {
			delete m_Material;
			m_Material = 0;
		}
	};

	void Initialize(Vertex* vert, size_t vertSize,ULONG* indi,size_t indiSize,Material *Mat);
	void Render(MatrixBuffer _MatrixBuffer);


	Vertex* GetVertices() { return vertices; }
	ULONG* GetIndices() { return indices; }
	size_t GetVertexSize() { return verticesSize; }
	size_t GetIndexSize() { return indicesSize; }
	Material* GetMaterial() { return m_Material; }
};