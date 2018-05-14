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
	// �Է� �������� �������� ���� ����� ���� ���� ��� �����Ϳ� ����
	output.pi_Position = input.vi_Position * m_MatrixBuffer.world;
	output.pi_Texcoord = input.vi_Texcoord;
	output.pi_Color = input.vi_Color;
	return output;
}

ULONG TextureShader::pixelShader(PixelShaderInput input)
{
	ULONG finalColor;
	// �ؽ��� ���ø�
	finalColor = m_ShaderTexture->TextureSample(input.pi_Texcoord);

	return finalColor;
}

