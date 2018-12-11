#include "GameSys.h"
#include "User.h"
#include "Scene.h"
#include "Graphics.h"
#include "SRTTest.h"

// ����� ���� ��ȯ��Ģ�� ��������.

SRTTest::SRTTest()
{
	scaling = { 1, 1 }; // 0�� 0,,, 1�� 100�ۼ�Ʈ    ,,�����Ͽ� ���õ� �ʱ�ȭ�� �⺻�� 1�� �ʱ�ȭ�Ѵ�.
	rotation = { 0, 0, 0 };
	translation = { 0, 0 };

}

SRTTest::~SRTTest()
{
}

bool SRTTest::Init(Graphics * _pGraphics)
{
	if (_pGraphics)
		pGraphics = _pGraphics;
	else
		return false;

	UINT vertexCount = 3;

	Vertex* vertex = new Vertex[vertexCount];
	vertex[0] = Vertex(50, 0, 0xffff0000);
	vertex[1] = Vertex(100, 50 * tanf(D3DX_PI / 3), 0xff0000ff);
	vertex[2] = Vertex(0, 50* tanf(D3DX_PI /3), 0xff00ff00);

	UINT vertexSize = sizeof(Vertex)* vertexCount;

	HRESULT result = DEVICE->CreateVertexBuffer(vertexSize,
		0, Vertex::fvf, D3DPOOL_DEFAULT, &vertexBuffer, NULL);

	if (FAILED(result))
		return false;

	void* vertexData = NULL;

	// 0���� ���ؽ������ŭ ���ý����۸� ���� �о�´�.
	result = vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	if (FAILED(result))
		return false;

	// ���ؽ����ۿ� ,,,,,  ������ ���ؽ� ������ ī���ϴ°�
	memcpy(vertexData, vertex, vertexSize);

	vertexBuffer->Unlock();

	delete[] vertex;

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	float fWidth = (float)viewport.Width;
	float fHeight = (float)viewport.Height;

		
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, fWidth, fHeight, 0.0f, -1, 1);   // ����Ʈ, ����Ʈ, ����, ž , �ش翵���� ���� ��������

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);


	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // �޸��� �׷���.
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);



	// �׵������ ���� �ʱ�ȭ�Ѵ�.
	D3DXMatrixIdentity(&world);


	return true;
}

void SRTTest::Update()
{
	if (INPUT->KeyPress(VK_RIGHT))
	{
		translation.x++;
	}
	if (INPUT->KeyPress(VK_LEFT))
	{
		translation.x--;
	}
	if (INPUT->KeyPress(VK_UP))
	{
		translation.y--;
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		translation.y++;
	}

	D3DXMATRIX center, invCenter; // ��İ� �� ����� ������� ������

	//  ���              �����
	// �̵����          ���̳ʽ�
	// ȸ�����            ����
	// �����̼����      ��ü���

	D3DXMatrixTranslation(&center, 50, 50, 0);
	D3DXMatrixInverse(&invCenter, NULL, &center);

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, translation.x, translation.y, 0); // T( Translation )��Ʈ������ ����
	
	if (INPUT->KeyPress('W'))
	{
		scaling.y += 0.1f;
	}
	if (INPUT->KeyPress('S'))
	{
		scaling.y -= 0.1f;
	}
	if (INPUT->KeyPress('A'))
	{
		scaling.x -= 0.1f;
	}
	if (INPUT->KeyPress('D'))
	{
		scaling.x += 0.1f;
	}

	D3DXMATRIX S, matS;
	D3DXMatrixScaling(&matS, scaling.x, scaling.y, 1); // �����Ͽ� ���õ� �ʱ�ȭ�� �⺻�� 1�� �ʱ�ȭ�Ѵ�.

	S = invCenter * matS * center; //

	if (INPUT->KeyPress('I'))
	{
		rotation.z += 0.1f;
	}
	if (INPUT->KeyPress('K'))
	{
		rotation.z -= 0.1f;
	}

	D3DXMATRIX R, matR;
	D3DXMatrixRotationZ(&matR, rotation.z);

	R = invCenter * matR * center; // ����Ŀ� ��ȯ����� ���ؼ� �������

	world = S * R * T;	// ���� �߿� ( ����� ���� ��ȯ��Ģ�� �������� )
	
}

void SRTTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf); // ���ؽ����� �����ϰ�
	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));// ��� �о�ð����� ������ ����
	DEVICE->SetTransform(D3DTS_WORLD, &world); // ���� ��������� ������ ���������ο� ����
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1); // �׷��ش�
}
