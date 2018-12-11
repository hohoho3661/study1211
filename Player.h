#pragma once

class Animator;
class World;

class Player
{
	enum AniState
	{
		IDLE,
		RUN,
		ATTACK,
	};

	std::vector<Animator*>	actions;

//	D3DXVECTOR2				pos;

	AniState				state;
	
	float h[6];
	float w[6];
	float y[6];
	float x[6];

	World*					world;


public:
	Player();
	~Player();

	void Update();
	void Render();

	void LoadXml();

	World* GetWorld() { return world; }
};

