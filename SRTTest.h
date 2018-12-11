#pragma once


// 월드변환
class SRTTest : public Scene
{
	struct Vertex // 클래스내에 버텍스를 만드는것
	{
		D3DXVECTOR3		position;
		DWORD			color;

		static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

		Vertex(){}
		Vertex(float x, float y, DWORD _color)
		{
			position = { x,y,0 };
			color = _color;
		}
	};

	// 사용할 버텍스에 대한 선언
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	// 위치벡터
	D3DXVECTOR2 scaling;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 translation;
	
	// 월드행렬
	D3DXMATRIX	world;
	D3DXMATRIX	projection;

public:
	SRTTest();
	~SRTTest();

	bool Init(Graphics* _pGraphics);
	void Update();
	void Render();
};

