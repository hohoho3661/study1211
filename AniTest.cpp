#include "GameSys.h"
#include "User.h"

#include "AniTest.h"

#include "Animator.h"

AniTest::AniTest()
{
	// 상태 초기화
	state = STAND;

	// Texture를 등록
	Texture* stand1 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 4, 2 }, { 34, 40 });
	Texture* stand2 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 35, 2 }, { 64, 40 });
	Texture* stand3 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 64, 2 }, { 93, 40 });

	Texture* run1 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 107, 1 }, { 137, 41 });
	Texture* run2 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 139, 1 }, { 168, 41 });
	Texture* run3 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 168, 1 }, { 200, 41 });
	Texture* run4 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 201, 1 }, { 234, 41 });
	Texture* run5 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 235, 1 }, { 265, 41 });
	Texture* run6 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 266, 1 }, { 297, 41 });
	Texture* run7 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 298, 1 }, { 329, 41 });
	Texture* run8 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 330, 1 }, { 365, 41 });
	Texture* run9 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 366, 1 }, { 400, 41 });


	Texture* attack1 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 0, 58 }, { 52, 100 });
	Texture* attack2 = Texture::Add(TEXT("Image/metalslug.png"),
		{ 53, 58 }, { 106, 100 });



	// Animator 설정
	std::vector<AnimationClip> clips;
	clips.push_back(AnimationClip(stand1, 100));
	clips.push_back(AnimationClip(stand2, 100));
	clips.push_back(AnimationClip(stand3, 100));
	actions.push_back(new Animator(&clips, Type::LOOP));
	clips.clear();

	//clips.push_back(AnimationClip(run1, 100));
	clips.push_back(AnimationClip(run2, 100));
	clips.push_back(AnimationClip(run3, 100));
	clips.push_back(AnimationClip(run4, 100));
	clips.push_back(AnimationClip(run5, 100));
	clips.push_back(AnimationClip(run6, 100));
	clips.push_back(AnimationClip(run7, 100));
	clips.push_back(AnimationClip(run8, 100));
	clips.push_back(AnimationClip(run9, 100));
	actions.push_back(new Animator(&clips, Type::LOOP));
	clips.clear();


	clips.push_back(AnimationClip(attack1, 100));
	clips.push_back(AnimationClip(attack2, 100));
	actions.push_back(new Animator(&clips, Type::LOOP));
	clips.clear();

	actions[state]->Play();
	pos = { GAME_WIDTH / 2, GAME_HEIGHT / 2 };
	scale = { 3, 3 };

	D3DXMatrixIdentity(&world);
}

AniTest::~AniTest()
{
	for (auto a : actions)
		delete a;
}

bool AniTest::Init()
{
	return true;
}

void AniTest::Update()
{
	state = STAND;


	if (KEYDOWN(VK_RIGHT) || KEYDOWN(VK_LEFT))
	{
		actions[RUN]->Play();
	}

	if (KEYPRESS(VK_RIGHT))
	{
		state = RUN;
		scale.x = 3;		// 피벗 위치를 기준으로 바뀜
	}
	if (KEYPRESS(VK_LEFT))
	{
		state = RUN;
		scale.x = -3;
	}
	if (KEYDOWN(VK_SPACE))
	{
		actions[ATTACK]->Play();
	}
	if (KEYPRESS(VK_SPACE))
	{
		state = ATTACK;
	}

	D3DXMATRIX S, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1);
	D3DXMatrixTranslation(&T, pos.x, pos.y, 0);

	world = S * T;

	actions[state]->Update();
}

void AniTest::Render()
{
	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	DEVICE->SetTransform(D3DTS_WORLD, &world);

	actions[state]->Render();
}
