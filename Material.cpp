#include "stdafx.h"
#include "Material.h"


Material::Material()
{
}


Material::~Material()
{
}

void Material::Render(Mesh * MeshToDraw, ConstantBuffer cBufferToDraw)
{
	if (cShader) {
		cShader->Render(MeshToDraw, cBufferToDraw,mTexture);
	}
	return;
}
