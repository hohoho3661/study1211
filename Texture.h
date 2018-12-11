#pragma once
#include "Constants.h"

class Texture
{
	struct Vertex
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 uv;

		static const DWORD fvf = D3DFVF_XYZ | D3DFVF_TEX1;

		Vertex() {}
		Vertex(float x, float y, float u, float v)
		{
			position = { x, y, 0 };
			uv = { u, v };
		}
	};

	UINT				number;
	LPDIRECT3DTEXTURE9	texture;
	D3DXVECTOR2			textureSize;

	D3DXVECTOR2			cutStart;
	D3DXVECTOR2			cutEnd;
	D3DXVECTOR2			uvStart;
	D3DXVECTOR2			uvEnd;

	static LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	static std::vector<Texture*>					textures;
	static std::map<tstring, LPDIRECT3DTEXTURE9>	textureMap;

	Texture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 cutStart, D3DXVECTOR2 cutEnd);
	~Texture();

	static void CreateVertexBuffer();

public:

	static Texture* Add(tstring fileName,
		D3DXVECTOR2	cutStart = D3DXVECTOR2(0.0f, 0.0f),
		D3DXVECTOR2	cutEnd = D3DXVECTOR2(0.0f, 0.0f));

	static void ReleaseInstance();


	void Render();

	void GetTextureSize(D3DXVECTOR2* size) const
	{
		*size = textureSize;
	}

	void GetRealSize(D3DXVECTOR2* size) const
	{
		*size = cutEnd - cutStart;
	}

};

