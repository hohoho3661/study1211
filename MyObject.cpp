#include "GameSys.h"
#include "User.h"
#include "World.h"
#include "MyObject.h"

MyObject::MyObject()
{
	texture = Texture::Add(TEXT("Image/character.png"));
	world = new World;
	world->SetPosition({ 300,500 });
	world->SetScale({ 0.2f, 0.2f });
	texture->GetRealSize(world->GetSize());

	world->SetBox();
}

MyObject::~MyObject()
{
	SAFE_DELETE(world);
}

void MyObject::Update()
{
	world->Update();
}

void MyObject::Render()
{
	world->SetWorld();
	texture->Render();
}
