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

	// ���ؽ��� �簢���� �����
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

	// ���ؽ����ۿ� ������ �־����
	void* vertexData = NULL;
	result = vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	if (FAILED(result))
		return false;

	memcpy(vertexData, vertex, vertexSize);

	vertexBuffer->Unlock();

	// ������� ���ý��� �����
	delete[] vertex;

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport); // ȭ�� ����� ����

	// D3DVIEWPORT9 �ڷ����� ��κ� �������̶� float���� �������ذ�,, �� ��ȯ ������
	float fWidth = static_cast<float>(viewport.Width);
	float fHeight = static_cast<float>(viewport.Height);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, fWidth, fHeight, 0.0f, -1, 1); // ���� viewport������ ����(�ٷ������� �������� ����� �ٶ�) ������ ����
																				 // cf) D3DXMatrixPerspective �̰� �񽺵��� �ٶ󺸴°�
	//D3DXMatrixPerspectiveOffCenterLH(&projection, 0.0f, fWidth, fHeight, 0.0f, -1, 1);
	

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);	// ���������� �����ϱ� ��İ� ����,, �׷��ϱ� false�� �س���


	// �׵� ��� ex) 4x4���� 1000,0100,0010,0001
	// �ʱ�ȭ�۾��̶�� �����ϸ��.
	D3DXMatrixIdentity(&world); 
	D3DXMatrixIdentity(&world2);
	
	return true;
}

void WVPtest::Update()
{
	if (INPUT->KeyPress(VK_RIGHT))
	{
		worldPos.x++; // ��ġ���͸� �Ȱ���
	}
	if (INPUT->KeyPress(VK_LEFT))
	{
		worldPos.x--;
	}
	if (INPUT->KeyPress(VK_UP))
	{
		worldPos.y--; // ��ġ���͸� �Ȱ���
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		worldPos.y++;
	}

	D3DXMatrixTranslation(&world, worldPos.x, worldPos.y, 0); // ����� ��ġ���͸� ������Ŀ� ����.

	if (INPUT->KeyPress('S'))
	{
		cameraPos.y--; // ī�޶� ��ġ ����
	}
	if (INPUT->KeyPress('W'))
	{
		cameraPos.y++;
	}
	if (INPUT->KeyPress('A'))
	{
		cameraPos.x++; // ī�޶� ��ġ ����
	}
	if (INPUT->KeyPress('D'))
	{
		cameraPos.x--;
	}

	D3DXMatrixTranslation(&view, cameraPos.x, cameraPos.y, 0); // ī�޶� �ٶ󺸴� ��ġ�� �ٲ���.
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
