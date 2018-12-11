#include "GameSys.h"
#include "User.h"

#include "Player.h"
#include "Animator.h"

#include "World.h"

Player::Player()
{
	world = new World;

	state = IDLE;
	LoadXml();

	
	actions[state]->Play();


	world->SetPosition({ 500, 500 });


//	actions[state]->GetTexture()->GetRealSize(&world->GetSize());

	D3DXVECTOR2 size;
	actions[state]->GetTexture()->GetRealSize(&size);
	world->SetSize(size);

}


Player::~Player()
{
	for (auto a : actions)
		delete a;
}

void Player::Update()
{
	state = IDLE;

	if (KEYPRESS(VK_F1))
	{
		state = RUN;

		actions[state]->Play();
	}
	if (KEYPRESS(VK_F2))
	{
		state = ATTACK;
		actions[state]->Play();
	}



	if (KEYDOWN(VK_LEFT))
	{
		D3DXVECTOR3 rot = { 0, D3DX_PI, 0 };
		world->SetRotation(rot);
	}
	if (KEYPRESS(VK_LEFT))
	{
		D3DXVECTOR2 move = { 3.f ,0 };
		world->SetPosition( world->GetPosition() - move );
	}

	if (KEYDOWN(VK_RIGHT))
	{
		D3DXVECTOR3 rot = { 0, 0, 0 };
		world->SetRotation(rot);
	}
	if (KEYPRESS(VK_RIGHT))
	{
		D3DXVECTOR2 move = { 3.f ,0 };
		world->SetPosition( world->GetPosition() + move );
	}



	actions[state]->Update();
	world->Update();
}

void Player::Render()
{
	//D3DXMATRIX world;
	//D3DXMatrixTranslation(&world, pos.x, pos.y, 0);
	//DEVICE->SetTransform(D3DTS_WORLD, &world);

	world->SetWorld();
	actions[state]->Render();
}

void Player::LoadXml()
{	
//	std::string str;

	XmlDocument* doc = new XmlDocument;
	Xml::XMLError err = doc->LoadFile("Megaman.xml");
	assert(doc != NULL);

	XmlElement* player = doc->FirstChildElement("TextureAtlas");
//	XmlAttribute* path = (XmlAttribute*)player->FirstAttribute();
//	str = path->Value();

//	unsigned int height = player->UnsignedAttribute("height");
//	unsigned int width = player->UnsignedAttribute("width");


	XmlElement* action = NULL;
	action = player->FirstChildElement();

	for (; action != NULL; action = action->NextSiblingElement())
	{
	//	unsigned int type = action->UnsignedAttribute("type");
	//	unsigned int time = action->UnsignedAttribute("time");
		
		XmlElement* sprite = action->FirstChildElement("sprite");
		for (int i = 0; sprite != NULL;sprite = sprite->NextSiblingElement(), i++)
		{
			h[i] = sprite->FloatAttribute("h");
			w[i] = sprite->FloatAttribute("w");
			y[i] = sprite->FloatAttribute("y");
			x[i] = sprite->FloatAttribute("x");

		}	
	}	


	// Texture를 등록
	Texture* idle1 = Texture::Add(TEXT("Image/Megaman.png"),
		{ x[0], y[0] }, { x[0] + w[0], y[0] + h[0] });
	Texture* idle2 = Texture::Add(TEXT("Image/Megaman.png"),
		{ x[1], y[1] }, { x[1] + w[1], y[1] + h[1] });

	// Texture를 등록
	Texture* run1 = Texture::Add(TEXT("Image/Megaman.png"),
		{ x[2], y[2] }, { x[2] + w[2], y[2] + h[2] });
	Texture* run2 = Texture::Add(TEXT("Image/Megaman.png"),
		{ x[3], y[3] }, { x[3] + w[3], y[3] + h[3] });
	Texture* run3 = Texture::Add(TEXT("Image/Megaman.png"),
		{ x[4], y[4] }, { x[4] + w[4], y[4] + h[4] });



	Texture* attack1 = Texture::Add(TEXT("Image/Megaman.png"),
		{ x[5], y[5] }, { x[5] + w[5], y[5] + h[5] });



	// Animator 설정
	std::vector<AnimationClip> clips;
	clips.push_back(AnimationClip(idle1, 100));
	clips.push_back(AnimationClip(idle2, 100));
	actions.push_back(new Animator(&clips, Type::LOOP));
	clips.clear();

	clips.push_back(AnimationClip(run1, 100));
	clips.push_back(AnimationClip(run2, 100));
	clips.push_back(AnimationClip(run3, 100));
	actions.push_back(new Animator(&clips, Type::LOOP));
	clips.clear();

	clips.push_back(AnimationClip(attack1, 100));
	actions.push_back(new Animator(&clips, Type::LOOP));
	clips.clear();



	delete doc; // 용량이 꽤 크다. new로 만들었으면 delete로 지우자
}
