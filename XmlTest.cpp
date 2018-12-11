#include "GameSys.h"
#include "User.h"
#include "XmlTest.h"
#include "World.h"

#include "Player.h"
#include "MyObject.h"

XmlTest::XmlTest()
{
	player = new Player;
	obj = new MyObject;
}

XmlTest::~XmlTest()
{
}

bool XmlTest::Init()
{
	return true;
}

void XmlTest::Update()
{
	player->Update();
	obj->Update();

	if (player->GetWorld()->IsCollision(obj->GetWorld()))
	{
		D3DXVECTOR2 back = { -30.f, 0.f };
		player->GetWorld()->SetPosition((player->GetWorld()->GetPosition()) + back);
	}
}

void XmlTest::Render()
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	player->Render();
	obj->Render();
}
