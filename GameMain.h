#pragma once
#include "GameBase.h"

class Scene;
class Camera;

class GameMain :
	public GameBase
{
private:
	Camera * camera;
	Scene * pScene;

public:
	GameMain();
	virtual ~GameMain();

	void Init(HWND hWnd);
	void Update();
	void Render();	

	void ReleaseAll();
	void ResetAll();
};

