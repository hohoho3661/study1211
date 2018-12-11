#pragma once

class Planet;
class Camera;

class SolarSystem : public Scene
{
	Texture*	back;
	D3DXMATRIX	bgWorld;

	Planet*		sun;
	Planet*		earth;
	Planet*		moon;



	//D3DXMATRIX	proj; // ī�޶� ��ü

public:
	SolarSystem();
	~SolarSystem();

	bool Init();
	void Update();
	void Render();

};

