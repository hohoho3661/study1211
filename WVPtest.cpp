#include "GameSys.h"
#include "User.h"
#include "Scene.h"
#include "Graphics.h"
#include "WVPtest.h"

WVPtest::WVPtest()
{
	worldPos = { 0, 0 };
	cameraPos = { 0, 0 };
}

WVPtest::~WVPtest()
{
	vertexBuffer->Release();
}

bool WVPtest::Init(Graphics * _pGraphics)
{
	if (_pGraphics)
		pGraphics = _pGraphics;
	else
		return false;

	// 버텍스로 사각형을 만들고
	UINT vertexCount = 6;

	Vertex* vertex = new Vertex[vertexCount];
	vertex[0] = Vertex(0, 0, 0xff00ff00);
	vertex[1] = Vertex(100, 0, 0xffff0000);
	vertex[2] = Vertex(0, 100, 0xffff0000);
	vertex[3] = Vertex(0, 100, 0xffff0000);
	vertex[4] = Vertex(100, 0, 0xffff0000);
	vertex[5] = Vertex(100, 100, 0xffff0000);

	UINT vertexSize = sizeof(Vertex)* vertexCount;

	HRESULT result = DEVICE->CreateVertexBuffer(
		vertexSize, 0, Vertex::fvf, D3DPOOL_DEFAULT,
		&vertexBuffer, NULL);

	if (FAILED(result))
		return false;

	// 버텍스버퍼에 정보를 넣어놓고
	void* vertexData = NULL;
	result = vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	if (FAILED(result))
		return false;

	memcpy(vertexData, vertex, vertexSize);

	vertexBuffer->Unlock();

	// 만들었던 버택스는 지우고
	delete[] vertex;

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport); // 화면 사이즈를 얻음

	// D3DVIEWPORT9 자료형은 대부분 정수형이라서 float으로 변경해준것,, 형 변환 연산자
	float fWidth = static_cast<float>(viewport.Width);
	float fHeight = static_cast<float>(viewport.Height);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, fWidth, fHeight, 0.0f, -1, 1); // 얻어온 viewport영역에 직교(바로위에서 직각으로 평면을 바라봄) 투영을 적용
																				 // cf) D3DXMatrixPerspective 이건 비스듬히 바라보는것
	//D3DXMatrixPerspectiveOffCenterLH(&projection, 0.0f, fWidth, fHeight, 0.0f, -1, 1);
	

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);	// 재질정보가 없으니까 까맣게 나옴,, 그러니까 false로 해놓자


	// 항등 행렬 ex) 4x4에서 1000,0100,0010,0001
	// 초기화작업이라고 생각하면됨.
	D3DXMatrixIdentity(&world); 
	D3DXMatrixIdentity(&world2);
	
	return true;
}

void WVPtest::Update()
{
	if (INPUT->KeyPress(VK_RIGHT))
	{
		worldPos.x++; // 위치벡터를 옴겨줌
	}
	if (INPUT->KeyPress(VK_LEFT))
	{
		worldPos.x--;
	}
	if (INPUT->KeyPress(VK_UP))
	{
		worldPos.y--; // 위치벡터를 옴겨줌
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		worldPos.y++;
	}

	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0); // 변경된 위치벡터를 월드행렬에 적용.

	if (INPUT->KeyPress('S'))
	{
		cameraPos.y--; // 카메라 위치 변경
	}
	if (INPUT->KeyPress('W'))
	{
		cameraPos.y++;
	}
	if (INPUT->KeyPress('A'))
	{
		cameraPos.x++; // 카메라 위치 변경
	}
	if (INPUT->KeyPress('D'))
	{
		cameraPos.x--;
	}

	D3DXMatrixTranslation(&view, cameraPos.x, cameraPos.y, 0); // 카메라가 바라보는 위치를 바꿔줌.
	DEVICE->SetTransform(D3DTS_VIEW, &view);
}

void WVPtest::Render()
{
	DEVICE->SetFVF(Vertex::fvf);

	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));

	DEVICE->SetTransform(D3DTS_WORLD, &world);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);

	DEVICE->SetTransform(D3DTS_WORLD, &world2);
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
