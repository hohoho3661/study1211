#pragma once

class World;

class MyObject
{
	Texture*	texture;
	World*		world;

public:
	MyObject();
	~MyObject();

	void Update();
	void Render();

	World* GetWorld() { return world; }
};

