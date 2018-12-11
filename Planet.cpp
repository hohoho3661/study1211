#include "GameSys.h"
#include "User.h"
#include "Planet.h"

Planet::Planet(tstring fileName)
{
	pos = { 0, 0 };
	scale = { 1, 1 };
	angle = 0.0f;

	D3DXMatrixIdentity(&world);
	matParent = nullptr;

	texture = Texture::Add(fileName);
}

Planet::~Planet()
{
}

void Planet::Update()
{
	angle += 0.001f; // �ޱ��� ���ϴ� �ӵ� ( ȸ���ϴ� �ӵ� )

	D3DXVECTOR2 center;		// ���͸� ���Ұǵ�,,
	texture->GetRealSize(&center); // �̹����� ����� ���ͷ� ���� ( ������� ȸ����ų �� ������ (0, 0)�� �� )
	center *= 0.5f;

	D3DXMATRIX C, IC, matR, matS;
	D3DXMATRIX S, R, T;
	D3DXMatrixTranslation(&C, center.x, center.y, 0);
	D3DXMatrixInverse(&IC, NULL, &C);

	D3DXMatrixRotationZ(&matR, angle);
	R = IC * matR * C;
	//R = matR;

	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);
	S = IC * matS * C;
	//S = matR;

	D3DXMatrixTranslation(&T, pos.x, pos.y, 0);

	world = S * R * T;
	// = S *  T * R;


	if (matParent != nullptr) // Parent�� �����Ͱ� �Ѿ��������
	{
		world = world * *matParent; // world�� ������  --------> ��������� �״�� �����.
	}
}

void Planet::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &world);
	texture->Render();
}
