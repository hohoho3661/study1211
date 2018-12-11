#include "GameSys.h"
#include "User.h"
#include "Scene.h"
#include "Graphics.h"
#include "VertexBufferTest.h"

VertexBufferTest::VertexBufferTest()
{
	vertexCount = 6;
	vertex = NULL;
	pGraphics = NULL;
}

VertexBufferTest::~VertexBufferTest()
{
	pGraphics = NULL;
	vertexBuffer->Release();
}

bool VertexBufferTest::Init(Graphics* _pGraphics)
{
	if (_pGraphics)
		pGraphics = _pGraphics;
	else
		return false;

	vertex = new Vertex[vertexCount];
	vertex[0] = Vertex(100, 100, 0xffff0000);
	vertex[1] = Vertex(200, 100, 0xffff0000);
	vertex[2] = Vertex(100, 200, 0xffff0000);
	vertex[3] = Vertex(100, 200, 0xffff0000);
	vertex[4] = Vertex(200, 100, 0xffff0000);
	vertex[5] = Vertex(200, 200, 0xffff0000);

	UINT vertexSize = sizeof(Vertex)* vertexCount;

	HRESULT result = _pGraphics->get3DDevice()->CreateVertexBuffer(					// create를 썻으면 마지막에 release를 해주자
		vertexSize, 0, Vertex::fvf, D3DPOOL_DEFAULT, &vertexBuffer, NULL);

	if (FAILED(result))
		return false;

	void* vertexData = NULL;

	result = vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	if (FAILED(result))
		return false;

	memcpy(vertexData, vertex, vertexSize);

	vertexBuffer->Unlock();

	return true;
}

void VertexBufferTest::Update()
{
	if (INPUT->KeyPress(VK_RIGHT))
	{
		for (UINT i = 0; i < vertexCount; i++)
		{
			vertex[i].position.x++;
		}
	}
	if (INPUT->KeyPress(VK_LEFT))
	{
		for (UINT i = 0; i < vertexCount; i++)
		{
			vertex[i].position.x--;
		}
	}

	UINT vertexSize = sizeof(Vertex) * vertexCount;
	void* vertexData = NULL;

	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();
}

void VertexBufferTest::Render()
{
	pGraphics->get3DDevice()->SetFVF(Vertex::fvf);							// PrimitiveUp 없이 그리는 함수 (다이렉트11부터는 없어짐.)
	pGraphics->get3DDevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	pGraphics->get3DDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
