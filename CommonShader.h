#pragma once
#include "Vector.h"
#include "Texture.h"

struct Mesh;

struct VertexShaderInput{
	Vector3 vi_Position;
	Vector2 vi_Texcoord;
	ULONG vi_Color;
};

struct PixelShaderInput {
	Vector3 pi_Position;
	Vector2 pi_Texcoord;
	ULONG pi_Color;
};

struct ConstantBuffer {
	Matrix3 world;
	Matrix3 view;
	Matrix3 projection;
};

// ���� ���̴�
class CommonShader {

public:
	CommonShader() { }
	~CommonShader() { }
	// ���̴��� ����� �ؽ���
	Texture *m_ShaderTexture;
	// ���̴��� ����� ��Ʈ������
	ConstantBuffer m_ConstantBuffer;
	
	// ��ӹ��� �ڽ� Ŭ�������� �����ؼ� ����ϰ� �����Լ��� ����
	virtual PixelShaderInput vertexShader(VertexShaderInput) = 0;
	virtual ULONG pixelShader(PixelShaderInput) = 0;

	// �������� ���õ� ��� �۾� ó��
	void Render(Mesh *MeshToDraw, ConstantBuffer MatrixBufferToDraw, Texture *TextureToDraw);
private:
	// ���̴��� ���꿡 �ʿ��� �Ķ���͵� �� ��
	void SetShaderParameters(ConstantBuffer MatrixBufferToDraw, Texture *TextureToDraw);
	// ���̴��� ����Ͽ� ������
	void RenderShader(Mesh *MeshToDraw);
};