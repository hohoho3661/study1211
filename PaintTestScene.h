#pragma once
#include "Scene.h"

class PaintTestScene : public Scene
{
private:
	struct Vertex			// 랜더링 파이프라인을 거쳐 좌표 포멧이 완료된 정보,, 그래서 쓸 수 있음.
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

