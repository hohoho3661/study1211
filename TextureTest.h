#pragma once

class TextureTest : public Scene
{
	struct Vertex
	{
		D3DXVECTOR3			position;
		D3DXVECTOR2			uv;

		static const DWORD	fvf = D3DFVF_XYZ | D3DFVF_TEX1; // tex 1,2,...,8 ���ؽ�1���� uv��ǥ�� � ���� ( ���� �ǹ�,, ȿ���� �شٴ���,, �÷����� �� )

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

	LPDIRECT3DTEXTURE9 texture;				// ������ ���������� ���� ������(LP)

	int vertexCount;

public:
	TextureTest();
	~TextureTest();

	bool Init();
	void Update();
	void Render();
};

