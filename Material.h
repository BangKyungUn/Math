#pragma once
#include "CommonShader.h"
#include "Texture.h"


class Material
{
	CommonShader *cShader;
	Texture *mTexture;
public:
	Material();
	~Material();

	void Initialize(CommonShader* childShader, Texture* tex) {
		cShader = childShader;
		mTexture = tex;
		return;
	}
	void Render(Mesh*MeshToDraw, ConstantBuffer cBufferToDraw);
};

