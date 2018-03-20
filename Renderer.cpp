
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Vector.h"
#include "Matrix.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);
void drawRectangle(int x, int y);
void drawCircle(int PosX, int PosY, Vector2D Center, float Radius,Matrix2 Mat);
void drawline(Vector2D Origin, Vector2D Target, Matrix2 Rot);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}


void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	Vector2D Center(0, 0);
	
	// Draw
	SetColor(255, 0, 0);

	// Set Matrix
	static float angle = 0.0f;
	angle += 0.1f;

	Matrix2 Mat(2.0f, 2.0f, 0.0f, 1.0f);
	Matrix2 RotateMat(1.0f, 0.0f, 0.0f, 1.0f);

	RotateMat.SetRotate(angle);
	Mat = Mat * RotateMat;

	drawCircle(100, 100, Center, 50.0f,Mat);

	Vector2D Origin(0.0f, 0.0f);
	Vector2D Target(100.0f, 100.0f);

	drawline(Origin, Target,RotateMat);


	// Buffer Swap 
	BufferSwap();
}

void drawRectangle(int x, int y) {

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			PutPixel(i, j);
		}
	}
}

void drawCircle(int PosX, int PosY, Vector2D Center, float Radius, Matrix2 Mat) {
		
	for (int x = -Radius; x < Radius; x++) {
		for (int y = -Radius; y < Radius; y++) {
			Vector2D currentPos(x, y);
			if (Vector2D::DistSquared(Center, currentPos) < Radius * Radius) {
				Vector2D newPos = currentPos * Mat ;
				PutPixel(newPos.x, newPos.y);

			}
		}
	}
}

void drawline(Vector2D Origin, Vector2D Target, Matrix2 Rot) {

	int gradient = (Target.y - Origin.y) / (Target.x - Origin.x);
	int y = Origin.y;

	for (int i = Origin.x; i < Target.x; i++) {
		y += gradient;
		Vector2D pos(i, y);
		pos = pos * Rot;
		PutPixel(pos.x, pos.y);
	}
	
}