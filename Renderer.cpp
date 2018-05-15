
#include "stdafx.h"
#include "Vector.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Texture.h"
#include "Mesh.h"
#include "CommonShader.h"
#include "Material.h"
#include "TextureShader.h"
#include "Sprite.h"
#include "Input.h"
#include <map>
#include "Transform.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(IntPoint pt)
{
	if (!IsInRange(pt.X, pt.Y)) return;

	ULONG* dest = (ULONG*)g_pBits;

	int halfWidth = RoundToInt(g_nClientWidth * 0.5f);
	int halfHeight = RoundToInt(g_nClientHeight * 0.5f);

	DWORD offset = (halfHeight * g_nClientWidth - g_nClientWidth * pt.Y) + (halfWidth + pt.X);
	*(dest + offset) = g_CurrentColor;
}

void DrawLine(const Vector3& start, const Vector3& end)
{
	float length = (end - start).Dist();
	float inc = 1.0f / length;

	int maxLength = RoundToInt(length);
	for (int i = 0; i <= maxLength; i++)
	{
		float t = inc * i;
		if (t >= length) t = 1.0f;
		Vector3 Pt = start * (1.0f - t) + end * t;
		PutPixel(Pt.ToIntPoint());
	}

}

void Draw2DTriangle(Triangle t)
{
	for (int y = RoundToInt(t.sbbMin.Y); y < RoundToInt(t.sbbMax.Y); y++)
	{
		for (int x = RoundToInt(t.sbbMin.X); x < RoundToInt(t.sbbMax.X); x++)
		{
			Vector3 target((float)x, (float)y, 0.0f);
			float outS, outT;
			t.CalcBaryCentricCoord(target, &outS, &outT);
			if (t.IsInTrianble(outS, outT))
			{
				ULONG vColor = t.GetFragmentColor(target, outS, outT);
				if (g_Texture->IsLoaded())
				{
					g_CurrentColor = g_Texture->GetTexturePixel(outS, outT, t);
				}

				PutPixel(IntPoint(x, y));
			}			
		}
	}
}



// Global
Mesh *Mesh01, *Mesh02, *Mesh03;
Sprite Sprite01, Sprite02, Sprite03;
std::map<int, Sprite> spriteMap;
Input* cInput;

void InitFrame(void)
{
	cInput = new Input;
	// Texture Data
	g_Texture->LoadBMP("test.bmp");

	// Material Data
	Material *Mat = new Material;
	CommonShader* texShader = new TextureShader;
	Mat->Initialize(texShader, g_Texture);

	// Mesh Data
	// 버텍스 셋업
	Vector3 Pt1, Pt2, Pt3, Pt4;

	Pt1.SetPoint(-50, 50.0f);
	Pt2.SetPoint(50.0f, 50.0f);
	Pt3.SetPoint(50.0f, -50.0f);
	Pt4.SetPoint(-50.0f, -50.0f);

	Vertex *vert = new Vertex[4];

	vert[0].position = Pt1;
	vert[0].color = RGB(255, 0, 0);
	vert[0].uv = Vector2(0.0f, 0.0f);

	vert[1].position = Pt2;
	vert[1].color = RGB(0, 255, 0);
	vert[1].uv = Vector2(1.0f, 0.0f);

	vert[2].position = Pt3;
	vert[2].color = RGB(0, 0, 255);
	vert[2].uv = Vector2(1.0f, 1.0f);

	vert[3].position = Pt4;
	vert[3].color = RGB(255, 255, 0);
	vert[3].uv = Vector2(0.0f, 1.0f);

	
	ULONG* indices = new ULONG[6];
	// 첫번째 삼각형
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	// 두번쨰 삼각형
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 2;

	Mesh01 = new Mesh;
	Mesh02 = new Mesh;
	Mesh03 = new Mesh;

	// 메쉬 셋업
	Mesh01->Initialize(vert, 4, indices, 6,Mat);
	Mesh02->Initialize(vert, 4, indices, 6,Mat);
	Mesh03->Initialize(vert, 4, indices, 6, Mat);

	// 레이어가 낮은거부터 그려짐.
	// 왼쪽 스프라이트
	Sprite01.initialize(Mesh01, Vector3(-50.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.25f, 0);
	// 가운데 스프라이트
	Sprite02.initialize(Mesh02, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 45.0f), 0.25f, 2);
	// 오른쪽 스프라이트
	Sprite03.initialize(Mesh03, Vector3(50.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.25f, 1);

	// 정렬 및 검색을 용이하게 하기 위해 맵 사용
	// 입력 객체 생성
	std::pair<int, Sprite>p1(Sprite01.Layer, Sprite01);
	std::pair<int, Sprite>p2(Sprite02.Layer, Sprite02);
	std::pair<int, Sprite>p3(Sprite03.Layer, Sprite03);
	// 삽입
	spriteMap.insert(p1);
	spriteMap.insert(p2);
	spriteMap.insert(p3);

	return;
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// var initialize
	float offsetX = 0.0f;
	float angle = 0.0f;
	float scale = 1.0f;

	//if (GetAsyncKeyState(VK_LSHIFT)) cInput->calcCamera
	//else {
	//	offsetX = cInput->CalcOffset();
	//	angle = cInput->CalcAngle();
	//	scale = cInput->CalcScale();
	//}

	// 입력 처리
	offsetX = cInput->CalcOffset();
	angle = cInput->CalcAngle();
	scale = cInput->CalcScale();

	Matrix3 TMat, RMat, SMat, TRSMat, TRS;
	ConstantBuffer cBuffer01;
	Transform2D MeshTransform(Vector2(offsetX, 0.0f), angle, Vector2(scale, scale));
	TRS = MeshTransform.GetTRSMatrix();


	// SpriteMap의 처음부터 끝까지 돌면서 렌더링
	for (std::map<int, Sprite>::iterator i = spriteMap.begin(); i != spriteMap.end(); i++) {
		// 스프라이트의 기본 속성에 offset,angle,scale을 더하여  TRSMat을 만듬.
		TMat.SetTranslation(i->second.pos.X + offsetX, i->second.pos.Y);
		RMat.SetRotation(i->second.rot.Z + angle);
		SMat.SetScale(i->second.Scale + scale);
		TRSMat = TMat * RMat * SMat;
		// 매트릭스 버퍼의 월드 행렬에 TRSMat을 저장
		cBuffer01.world = TRSMat;
		i->second.m_Mesh->Render(cBuffer01);
	}

	// Buffer Swap 
	BufferSwap();
}
