#pragma once
class WVPtest : public Scene
{
	struct Vertex
	{
		D3DXVECTOR3		position;
		DWORD			color;

		static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

		Vertex() {}
		Vertex(float x, float y, DWORD _color)
		{
			position = { x,y,0};
			color = _color;
		}
	};

	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	// 2차원 벡터
	D3DXVECTOR2 worldPos;
	D3DXVECTOR2 cameraPos;

	// 행렬 만들기
	D3DXMATRIX world;
	D3DXMATRIX world2;
	D3DXMATRIX view;
	D3DXMATRIX projection;

public:
	WVPtest();
	~WVPtest();

	bool Init(Graphics* _pGraphics);
	void Update();
	void Render();
};

