#include "GameSys.h"
#include "User.h"
#include "Scene.h"

#include "TextureTest.h"



TextureTest::TextureTest()
{
	//// ���̷�Ʈ������ �̹����� ����ϱ����� �����۾��� ���� �̹�������� 2�� �������� ǥ�õǴ°� ��Ģ������.
	//D3DXCreateTextureFromFile(DEVICE, TEXT("Image/rocket.png"), &texture);
	
	// ���� ��Ʈ���ϱ� ������ �Լ��� ����ؼ� ������ �ذ��Ѵ�.
	D3DXCreateTextureFromFileEx(
		DEVICE,
		TEXT("Image/rocket.png"),
		D3DX_DEFAULT_NONPOW2,	// 2�� n������ ������ó���� �����ʰٴ�.
		D3DX_DEFAULT_NONPOW2,
		1, // ũ�� �ε��Ҷ� �����ɸ� (�̸��������� ó���ϴ� ��)
		NULL,
		D3DFMT_UNKNOWN, // D3DFMT_A8B8G8R8 �̷������� ����ص���.
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		RGB(255, 0, 255),	// ������ ���
		NULL,
		NULL,
		&texture
	);



	// �̹��� ������ �˾Ƽ� �̹���ũ�⿡ ���纸��
	D3DSURFACE_DESC decs;	// �����
	texture->GetLevelDesc(0, &decs); // ��´�.

	vertexCount = 6;
	vertex = new Vertex[vertexCount];
	//vertex[0] = Vertex(0, 0, 0, 0 );
	//vertex[1] = Vertex(400, 0, 1, 0 );
	//vertex[2] = Vertex(0, 400, 0, 1 );
	//vertex[3] = Vertex(0, 400, 0, 1 );
	//vertex[4] = Vertex(400, 0, 1, 0 );
	//vertex[5] = Vertex(400, 400, 1, 1 );
	vertex[0] = Vertex(0, 0, 0, 0);				
	vertex[1] = Vertex(decs.Width, 0, 1, 0);
	vertex[2] = Vertex(0, decs.Height, 0, 1);
	vertex[3] = Vertex(0, decs.Height, 0, 1);
	vertex[4] = Vertex(decs.Width, 0, 1, 0);
	vertex[5] = Vertex(decs.Width, decs.Height, 1, 1);

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.f, (float)viewport.Width, (float)viewport.Height, 0.f, -1, 1);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
}


TextureTest::~TextureTest()
{
	texture->Release();
}

bool TextureTest::Init()
{
	return true;
}

void TextureTest::Update()
{
}

void TextureTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetTexture(0, texture);

	// ���� ����

	// ���� ������ ����
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	
	// ���� ���� ��� ����
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); // ���������� �ϰٴٴ� ��

	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(Vertex));

	// ���� ������ ��
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
