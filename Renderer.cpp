
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
#include <vector>
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




Mesh *Mesh01, *Mesh02, *Mesh03;
Sprite Sprite01, Sprite02, Sprite03;
std::vector<Sprite*> spriteArray;

// 순차적으로 레이어 검사 후 재정렬
void sort(std::vector<Sprite*>&outArray) {
	std::vector<Sprite*>temp;
	for (int i = 0; i < 5; i++) {
		for (auto a : outArray) {
			if (a->Layer == i) {
				temp.push_back(a);
			}
		}
	}
	outArray = temp;
}

void InitFrame(void)
{

	// Texture Data
	g_Texture->LoadBMP("test.bmp");

	// Material Data
	Material *Mat = new Material;
	CommonShader* texShader = new TextureShader;
	Mat->Initialize(texShader, g_Texture);

	// Mesh Data
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

	Mesh01->Initialize(vert, 4, indices, 6,Mat);
	Mesh02->Initialize(vert, 4, indices, 6,Mat);
	Mesh03->Initialize(vert, 4, indices, 6, Mat);

	// 레이어가 낮은거부터 그려짐.
	// 왼쪽 스프라이트
	Sprite01.initialize(Mesh01, Vector3(-50.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.25f, 0);
	spriteArray.push_back(&Sprite01);

	// 가운데 스프라이트
	Sprite02.initialize(Mesh02, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 45.0f), 0.25f, 1);
	spriteArray.push_back(&Sprite02);

	// 오른쪽 스프라이트
	Sprite03.initialize(Mesh03, Vector3(50.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 0.25f, 2);
	spriteArray.push_back(&Sprite03);

	// 정렬
	sort(spriteArray);

	return;
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	static float offsetX = 0.0f;
	static float angle = 0.0f;
	static float scale = 1.0f;

	if (GetAsyncKeyState(VK_LEFT)) offsetX -= 1.0f;
	if (GetAsyncKeyState(VK_RIGHT)) offsetX += 1.0f;
	if (GetAsyncKeyState(VK_UP)) angle += 1.0f;
	if (GetAsyncKeyState(VK_DOWN)) angle -= 1.0f;
	if (GetAsyncKeyState(VK_PRIOR)) scale *= 1.01f;
	if (GetAsyncKeyState(VK_NEXT)) scale *= 0.99f;

	Matrix3 TMat, RMat, SMat, TRSMat;
	MatrixBuffer mBuffer01;


	for (auto a : spriteArray) {

		// 스프라이트의 기본 속성에 offset,angle,scale을 더하여  TRSMat을 만듬.
		TMat.SetTranslation(a->pos.X + offsetX, a->pos.Y);
		RMat.SetRotation(a->rot.Z + angle);
		SMat.SetScale(a->Scale + scale);
		TRSMat = TMat * RMat * SMat;
		// 매트릭스 버퍼의 월드 행렬에 TRSMat을 저장
		mBuffer01.world = TRSMat;
		// 변경된 매트릭스 버퍼를 셰이더에 넘겨서 렌더링.
		a->m_Mesh->Render(mBuffer01);
	}

	// Buffer Swap 
	BufferSwap();
}
