#pragma once
#include "CommonShader.h"
class TextureShader : public CommonShader
{
public:
	TextureShader();
	~TextureShader();

	// VertexShader , PixelShader ����
	virtual PixelShaderInput vertexShader(VertexShaderInput) override;
	virtual ULONG pixelShader(PixelShaderInput) override;
};

