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

struct MatrixBuffer {
	Matrix3 world;
};

// ���� ���̴�
class CommonShader {

public:
	CommonShader() { }
	~CommonShader() { }
	// ���̴��� ����� �ؽ���
	Texture *m_ShaderTexture;
	// ���̴��� ����� ��Ʈ������
	MatrixBuffer m_MatrixBuffer;
	
	// ��ӹ��� �ڽ� Ŭ�������� �����ؼ� ����ϰ� �����Լ��� ����
	virtual PixelShaderInput vertexShader(VertexShaderInput) = 0;
	virtual ULONG pixelShader(PixelShaderInput) = 0;

	// �������� ���õ� ��� �۾� ó��
	void Render(Mesh *MeshToDraw, MatrixBuffer MatrixBufferToDraw, Texture *TextureToDraw);
private:
	// ���̴��� ���꿡 �ʿ��� �Ķ���͵� �� ��
	void SetShaderParameters(MatrixBuffer MatrixBufferToDraw, Texture *TextureToDraw);
	// ���̴��� ����Ͽ� ������
	void RenderShader(Mesh *MeshToDraw);
};