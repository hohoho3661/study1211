#pragma once

class Planet;

class TextureTest1 : public Scene
{
	Texture* pTexture;

	Planet* pPlanet;

	D3DXMATRIX projection;

public:
	TextureTest1();
	~TextureTest1();

	bool Init();
	void Update();
	void Render();
};

