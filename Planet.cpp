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
	angle += 0.001f; // 앵글이 변하는 속도 ( 회전하는 속도 )

	D3DXVECTOR2 center;		// 센터를 구할건데,,
	texture->GetRealSize(&center); // 이미지의 가운데를 센터로 만듬 ( 원래라면 회전시킬 때 중점이 (0, 0)이 됨 )
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


	if (matParent != nullptr) // Parent에 포인터가 넘어와있으면
	{
		world = world * *matParent; // world에 곱해줌  --------> 월드행렬이 그대로 적용됨.
	}
}

void Planet::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &world);
	texture->Render();
}
