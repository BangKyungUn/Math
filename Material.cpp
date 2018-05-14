#include "stdafx.h"
#include "Material.h"


Material::Material()
{
}


Material::~Material()
{
}

void Material::Render(Mesh * MeshToDraw, MatrixBuffer MatrixBufferToDraw)
{
	if (cShader) {
		cShader->Render(MeshToDraw, MatrixBufferToDraw,mTexture);
	}
	return;
}
