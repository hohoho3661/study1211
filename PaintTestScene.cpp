#include "GameSys.h"
#include "User.h"
#include "Scene.h"
#include "Graphics.h"
#include "PaintTestScene.h"



PaintTestScene::PaintTestScene()
{
	state = LINE;
	selectColor = 0xff0000ff;
	pGraphics = NULL;
}

PaintTestScene::~PaintTestScene()
{
	lineVertex.clear();
	rectVertex.clear();
}

bool PaintTestScene::Init(Graphics* _pGraphics)
{
	if (_pGraphics == NULL)
		return false;

	this->pGraphics = _pGraphics;

	return true;
}

void PaintTestScene::Update()
{
	if (INPUT->KeyDown(VK_F1))
		state = LINE;
	if (INPUT->KeyDown(VK_F2))
		state = RECT;

	if (INPUT->KeyDown('1'))
		selectColor = 0xffff0000;
	
	if (INPUT->KeyDown(VK_LBUTTON))
	{
		Vertex startVertex = Vertex(mousePos.x, mousePos.y, selectColor);

		switch (state)
		{
		case PaintTestScene::LINE:
			lineVertex.push_back(startVertex);
			break;
		case PaintTestScene::RECT:
			rectVertex.push_back(startVertex);
			break;
		default:
			break;
		}
	}

	if (INPUT->KeyUp(VK_LBUTTON))
	{
		Vertex endVertex = Vertex(mousePos.x, mousePos.y, selectColor);

		switch (state)
		{
		case PaintTestScene::LINE:
			lineVertex.push_back(endVertex);
			break;
		case PaintTestScene::RECT:
		{
			Vertex v1, v2, v3, v4;

			D3DXVECTOR4 startPos = rectVertex.back().position;

			v1 = Vertex(mousePos.x, startPos.y, selectColor);
			v2 = Vertex(startPos.x, mousePos.y, selectColor);
			v3 = Vertex(startPos.x, mousePos.y, selectColor);
			v4 = Vertex(mousePos.x, startPos.y, selectColor);

			rectVertex.push_back(v1);
			rectVertex.push_back(v2);
			rectVertex.push_back(v3);
			rectVertex.push_back(v4);

			rectVertex.push_back(endVertex);
		}		
			break;
		default:
			break;
		}
	}
}

void PaintTestScene::Render()
{
	pGraphics->get3DDevice()->SetFVF(Vertex::fvf);

	pGraphics->get3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // 스테이트 정하기,, 평면으로 랜더

	if (lineVertex.size() > 1)
	{
		pGraphics->get3DDevice()->DrawPrimitiveUP(D3DPT_LINELIST, lineVertex.size()/2,
			lineVertex.begin()._Ptr, sizeof(Vertex));
	}

	if (rectVertex.size() > 1)
	{
		pGraphics->get3DDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, rectVertex.size()/3,
			rectVertex.begin()._Ptr, sizeof(Vertex));
	}
}
