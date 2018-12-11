#pragma once
#include "Scene.h"

class PaintTestScene : public Scene
{
private:
	struct Vertex			// ������ ������������ ���� ��ǥ ������ �Ϸ�� ����,, �׷��� �� �� ����.
	{
		D3DXVECTOR4		position;
		DWORD			color;

		static const DWORD fvf = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;

		Vertex(){}
		Vertex(float x, float y, DWORD _color)
		{
			position = { x,y,0,1 };
			color = _color;
		}
	};

	enum State
	{
		LINE,
		RECT,
	};

	State state;

	DWORD selectColor;

	std::vector<Vertex> lineVertex;
	std::vector<Vertex> rectVertex;


public:
	PaintTestScene();
	~PaintTestScene();

	bool Init(Graphics* _pGraphics);
	void Update();
	void Render();
};

