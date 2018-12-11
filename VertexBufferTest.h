#pragma once
#include "Scene.h"

class VertexBufferTest :
	public Scene
{
	struct Vertex
	{
		D3DXVECTOR4		position;
		DWORD			color;

		static const DWORD fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

		Vertex(){}
		Vertex(float x, float y, DWORD _color) 
		{
			position = { x, y, 0, 1 };
			color = _color;
		}
	};

	Vertex*					vertex;
	UINT					vertexCount;
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	
public:
	VertexBufferTest();
	~VertexBufferTest();

	bool Init(Graphics* _pGraphics);
	void Update();
	void Render();
};

