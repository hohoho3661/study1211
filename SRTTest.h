#pragma once


// ���庯ȯ
class SRTTest : public Scene
{
	struct Vertex // Ŭ�������� ���ؽ��� ����°�
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

	// ����� ���ؽ��� ���� ����
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	// ��ġ����
	D3DXVECTOR2 scaling;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 translation;
	
	// �������
	D3DXMATRIX	world;
	D3DXMATRIX	projection;

public:
	SRTTest();
	~SRTTest();

	bool Init(Graphics* _pGraphics);
	void Update();
	void Render();
};

