#include "stdafx.h"
#include "CommonShader.h"
#include "Mesh.h"

void CommonShader::Render(Mesh * MeshToDraw, MatrixBuffer MatrixBufferToDraw, Texture * TextureToDraw)
{
	SetShaderParameters(MatrixBufferToDraw, TextureToDraw);
	RenderShader(MeshToDraw);
	return;
}

void CommonShader::SetShaderParameters(MatrixBuffer MatrixBufferToDraw, Texture * TextureToDraw)
{
	m_ShaderTexture = TextureToDraw;
	m_MatrixBuffer = MatrixBufferToDraw;
	return;
}

void CommonShader::RenderShader(Mesh * MeshToDraw)
{
	// 버텍스 및 인덱스 정보를 가져옴
	Vertex *vertices = MeshToDraw->GetVertices();
	ULONG *indices = MeshToDraw->GetIndices();
	PixelShaderInput *pData = new PixelShaderInput[MeshToDraw->GetVertexSize()];
	Vertex *vert = new Vertex[MeshToDraw->GetVertexSize()];

	// 모든 버텍스에 대해서 버텍스 셰이더 연산
	for (int i = 0; i < MeshToDraw->GetVertexSize(); i++) {
		VertexShaderInput vData;
		vData.vi_Position = vertices[i].position;
		vData.vi_Texcoord = vertices[i].uv;
		vData.vi_Color = vertices[i].color;
		pData[i] = vertexShader(vData);

		vert[i].position = pData[i].pi_Position;
		vert[i].uv = pData[i].pi_Texcoord;
		vert[i].color = pData[i].pi_Color;
	}

	// 인덱스 / 3 = 삼각형 갯수
	// 삼각형 갯수 만큼 루프를 돌면서 픽셀 처리
	for (int i = 0; i < MeshToDraw->GetIndexSize() / 3; i++) {
		// 0 1 2 , 3 4 5
		Triangle tri(vert[indices[i*3]], vert[indices[i*3+1]], vert[indices[i*3+2]]);
		for (int y = tri.Min.Y; y <= tri.Max.Y; y++)
		{
			for (int x = tri.Min.X; x <= tri.Max.X; x++)
			{
				Vector3 target((float)x + 0.5f, (float)y + 0.5f, 0.0f);
				float outS = 0;
				float outT = 0;
				tri.CalcBaryCentricCoord(target, &outS, &outT);
				if (tri.IsInTrianble(outS, outT))
				{
					PixelShaderInput pData;
					pData.pi_Position = tri.GetFragmentPos(target, outS, outT);
					pData.pi_Color = tri.GetFragmentColor(target, outS, outT);
					pData.pi_Texcoord = tri.GetFragmentUV(target, outS, outT);
					ULONG finalColor = pixelShader(pData);
					g_CurrentColor = finalColor;
					PutPixel(IntPoint(x, y));
				}
			}
		}
	}
}
