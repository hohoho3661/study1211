#pragma once

class Animator;

class AniTest : public Scene
{
	enum AniState
	{
		STAND,
		RUN,
		ATTACK,
		JUMP,
	};

	AniState				state;
	std::vector<Animator*>	actions;

	D3DXVECTOR2				pos;
	D3DXVECTOR2				scale;

	D3DXMATRIX				world;


public:
	AniTest();
	~AniTest();

	bool Init();
	void Update();
	void Render();
};

