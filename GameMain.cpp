#include "GameSys.h"
#include "User.h"
#include "Scene.h"
#include "Texture.h"

#include "Camera.h"

#include "GameMain.h"
#include "PaintTestScene.h"
#include "VertexBufferTest.h"
#include "WVPTest.h"
#include "SRTTest.h"
#include "TextureTest.h"
#include "TextureTest1.h"
#include "SolarSystem.h"
#include "AniTest.h"
#include "XmlTest.h"

GameMain::GameMain()
{
}

GameMain::~GameMain()
{
	ReleaseAll();
}

void GameMain::Init(HWND hWnd)
{
	GameBase::Init(hWnd);

	pScene = new XmlTest;

	camera = new Camera;
	pScene->Init();
}

void GameMain::Update()
{
	pScene->Update();
	camera->Update();
}

void GameMain::Render()
{
	pScene->Render();
}

void GameMain::ReleaseAll()
{
	GameBase::ReleaseAll();
	
	SafeDelete(pScene);
	SafeDelete(camera);
	
	INPUT->Release();
	Texture::ReleaseInstance();
}

void GameMain::ResetAll()
{
	GameBase::ResetAll();
}