#include "stdafx.h"
#include "TextureShader.h"


TextureShader::TextureShader()
{
}


TextureShader::~TextureShader()
{
}

PixelShaderInput TextureShader::vertexShader(VertexShaderInput input)
{
	PixelShaderInput output;
	// 입력 데이터의 포지션의 월드 행렬을 곱한 것을 출력 데이터에 저장
	output.pi_Position = input.vi_Position * m_MatrixBuffer.world;
	output.pi_Texcoord = input.vi_Texcoord;
	output.pi_Color = input.vi_Color;
	return output;
}

ULONG TextureShader::pixelShader(PixelShaderInput input)
{
	ULONG finalColor;
	// 텍스쳐 샘플링
	finalColor = m_ShaderTexture->TextureSample(input.pi_Texcoord);

	return finalColor;
}

