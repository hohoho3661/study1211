#pragma once

class TextureTest : public Scene
{
	struct Vertex
	{
		D3DXVECTOR3			position;
		D3DXVECTOR2			uv;

		static const DWORD	fvf = D3DFVF_XYZ | D3DFVF_TEX1; // tex 1,2,...,8 버텍스1개에 uv좌표가 몇개 인지 ( 섞는 의미,, 효과를 준다던지,, 컬러패턴 등 )

		Vertex(){}
		Vertex(float x, float y, float u, float v)
		{
			position = { x,y,0 };
			uv = { u,v };
		}
	};

	Vertex* vertex;

	D3DXMATRIX world;
	D3DXMATRIX projection;

	LPDIRECT3DTEXTURE9 texture;				// 정보를 가지고있을 곳의 포인터(LP)

	int vertexCount;

public:
	TextureTest();
	~TextureTest();

	bool Init();
	void Update();
	void Render();
};

