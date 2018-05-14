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

// 공통 셰이더
class CommonShader {

public:
	CommonShader() { }
	~CommonShader() { }
	// 셰이더에 사용할 텍스쳐
	Texture *m_ShaderTexture;
	// 셰이더에 사용할 매트릭스들
	MatrixBuffer m_MatrixBuffer;
	
	// 상속받은 자식 클래스에서 수정해서 사용하게 가상함수로 선언
	virtual PixelShaderInput vertexShader(VertexShaderInput) = 0;
	virtual ULONG pixelShader(PixelShaderInput) = 0;

	// 렌더링에 관련된 모든 작업 처리
	void Render(Mesh *MeshToDraw, MatrixBuffer MatrixBufferToDraw, Texture *TextureToDraw);
private:
	// 셰이더에 연산에 필요한 파라미터들 셋 업
	void SetShaderParameters(MatrixBuffer MatrixBufferToDraw, Texture *TextureToDraw);
	// 셰이더를 사용하여 렌더링
	void RenderShader(Mesh *MeshToDraw);
};