
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
Matrix3 g_ShaderMatrix;

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
Mesh *Mesh01;
Matrix3 ModelMat, ViewMat;
Sprite Sprite01;
std::map<int, Sprite> spriteMap;
Input* cInput;

// Set Matrix
static float offsetX = 0.0f;
static float angle = 0.0f;
static float scale = 1.0f;
static Vector2 camLocation(0.0f, 0.0f);
static float camRotation = 0.0f;

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
	// ���ؽ� �¾�
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
	// ù��° �ﰢ��
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	// �ι��� �ﰢ��
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 2;

	Mesh01 = new Mesh;

	// �޽� �¾�
	Mesh01->Initialize(vert, 4, indices, 6,Mat);

	// ���̾ �����ź��� �׷���.
	// ���� ��������Ʈ
	Sprite01.initialize(Mesh01, 0);

	// ���� �� �˻��� �����ϰ� �ϱ� ���� �� ���
	// �Է� ��ü ����
	std::pair<int, Sprite>p1(Sprite01.Layer, Sprite01);

	// ����
	spriteMap.insert(p1);


	return;
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	//// var initialize
	//float offsetX = 0.0f;
	//float angle = 0.0f;
	//float scale = 1.0f;


	//if (GetAsyncKeyState(VK_LSHIFT)) cInput->calcCamera
	//else {
	//	offsetX = cInput->CalcOffset();
	//	angle = cInput->CalcAngle();
	//	scale = cInput->CalcScale();
	//}

	//// �Է� ó��
	//offsetX = cInput->CalcOffset();
	//angle = cInput->CalcAngle();
	//scale = cInput->CalcScale();

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		if (GetAsyncKeyState(VK_LEFT)) camLocation.X -= 1.0f;
		if (GetAsyncKeyState(VK_RIGHT)) camLocation.X += 1.0f;
		if (GetAsyncKeyState(VK_UP)) camLocation.Y += 1.0f;
		if (GetAsyncKeyState(VK_DOWN)) camLocation.Y -= 1.0f;
		if (GetAsyncKeyState(VK_PRIOR)) camRotation += 1.0f;
		if (GetAsyncKeyState(VK_NEXT)) camRotation -= 1.0f;
	}
	else
	{
		if (GetAsyncKeyState(VK_LEFT)) offsetX -= 1.0f;
		if (GetAsyncKeyState(VK_RIGHT)) offsetX += 1.0f;
		if (GetAsyncKeyState(VK_UP)) angle += 1.0f;
		if (GetAsyncKeyState(VK_DOWN)) angle -= 1.0f;
		if (GetAsyncKeyState(VK_PRIOR)) scale *= 1.01f;
		if (GetAsyncKeyState(VK_NEXT)) scale *= 0.99f;
	}

	// Transform SetUp
	Transform2D ModelTransform(Vector2(offsetX, 0.0f), angle, scale);
	spriteMap[0].trans = ModelTransform;

	Transform2D CameraTransform(camLocation, camRotation, 1.0f);
	Matrix3 ViewMat = CameraTransform.GetViewMatrix();


	// Axis Draw - X
	Vector3 XStart((float)g_nClientWidth * -0.5f, 0.0f, 1.0f);
	Vector3 XEnd((float)g_nClientWidth * 0.5f, 0.0f, 1.0f );
	XStart.X += CameraTransform.Location.X;
	XEnd.X += CameraTransform.Location.X;
	SetColor(255, 0, 0);
	DrawLine(XStart * ViewMat, XEnd * ViewMat);
	// Axis Draw - Y
	Vector3 YStart(0.0f, (float)g_nClientHeight * -0.5f, 1.0f);
	Vector3 YEnd(0.0f, (float)g_nClientHeight * 0.5f, 1.0f);
	YStart.Y += CameraTransform.Location.Y;
	YEnd.Y += CameraTransform.Location.Y;
	SetColor(0, 255, 0);
	DrawLine(YStart * ViewMat, YEnd * ViewMat);

	ConstantBuffer cBuffer01;
	Matrix3 ModelMat;

	// SpriteMap�� ó������ ������ ���鼭 ������
	for (std::map<int, Sprite>::iterator i = spriteMap.begin(); i != spriteMap.end(); i++) {
		//// ��������Ʈ�� �⺻ �Ӽ��� offset,angle,scale�� ���Ͽ�  TRSMat�� ����.
		//TMat.SetTranslation(i->second.pos.X + offsetX, i->second.pos.Y);
		//RMat.SetRotation(i->second.rot.Z + angle);
		//SMat.SetScale(i->second.Scale + scale);
		//TRSMat = TMat * RMat * SMat;
		//// ��Ʈ���� ������ ���� ��Ŀ� TRSMat�� ����
		ModelMat = i->second.trans.GetTRSMatrix();
		g_ShaderMatrix = ViewMat * ModelMat;
		cBuffer01.world = g_ShaderMatrix;
		i->second.m_Mesh->Render(cBuffer01);
	}

	// Buffer Swap 
	BufferSwap();
}
