#include "GameSys.h"
#include "User.h"

#include "Planet.h"
#include "Camera.h"

#include "SolarSystem.h"

// 객체에 대해,,,,,  월드행렬(SRT)을 적용하는 여러가지 방법을 연습해보자.

SolarSystem::SolarSystem()
{
	back = Texture::Add(TEXT("Image/background.jpg"));

	sun = new Planet(TEXT("Image/sun.png"));

	sun->SetScale({ 0.15f, 0.15f });

	earth = new Planet(TEXT("Image/earth.png"));

	earth->SetScale({ 0.2f, 0.2f });
	earth->SetPos({ 900, 0 });
	earth->SetParent(sun->getWorld());


	moon = new Planet(TEXT("Image/moon.png"));
	
	moon->SetScale({ 0.7f, 0.7f });
	moon->SetPos({ 1200,0 });
	moon->SetParent(earth->getWorld());



	// 사이즈를 얻어오고
	D3DXVECTOR2	bgSize;
	back->GetRealSize(&bgSize);

	D3DXVECTOR2 scale;
	scale.x = GAME_WIDTH / bgSize.x;
	scale.y = GAME_HEIGHT / bgSize.y;
	D3DXMatrixScaling(&bgWorld, scale.x, scale.y, 1);


	//// 카메라가 대체
	//D3DXMatrixOrthoOffCenterLH(&proj, 0.f, GAME_WIDTH, GAME_HEIGHT, 0.f, -1, 1);
	//DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
	//DEVICE->SetRenderState(D3DRS_LIGHTING, false);
}


SolarSystem::~SolarSystem()
{
	delete sun;
	delete earth;
	delete moon;

}

bool SolarSystem::Init()
{
	return true;
}

void SolarSystem::Update()
{
	if (KEYPRESS(VK_RIGHT))
	{
		sun->SetPos({ sun->GetPos().x + 2, sun->GetPos().y });
	}
	if (KEYPRESS(VK_LEFT))
	{
		sun->SetPos({ sun->GetPos().x - 2, sun->GetPos().y });
	}
	if (KEYPRESS(VK_UP))
	{
		sun->SetPos({ sun->GetPos().x, sun->GetPos().y - 2 });
	}
	if (KEYPRESS(VK_DOWN))
	{
		sun->SetPos({ sun->GetPos().x, sun->GetPos().y + 2 });
	}

	sun->Update();
	earth->Update();
	moon->Update();
}

void SolarSystem::Render()
{
	DEVICE->SetTransform(D3DTS_WORLD, &bgWorld);


	back->Render();

	sun->Render();
	earth->Render();
	moon->Render();

}
