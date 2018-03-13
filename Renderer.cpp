
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Vector.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);
void drawRectangle(int x, int y);
void drawCircle(int PosX, int PosY, Vector2D Center, float Radius);

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

	drawCircle(100, 100, Center, 50.0f);
	

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

void drawCircle(int PosX, int PosY, Vector2D Center, float Radius) {
		

	for (int x = -Radius; x < Radius; x++) {
		for (int y = -Radius; y < Radius; y++) {
			Vector2D currentPos(x, y);
			if(Vector2D::DistSquared(Center, currentPos) < Radius * Radius)
			PutPixel(x,y);
		}
	}
}