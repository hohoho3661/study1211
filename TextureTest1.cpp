#include "GameSys.h"
#include "User.h"
#include "TextureTest1.h"
#include "Planet.h"

TextureTest1::TextureTest1()
{
	pTexture = Texture::Add(TEXT("Image/background.jpg"));

	pPlanet = new Planet(TEXT("Image/sun.png"));

	D3DXMatrixOrthoOffCenterLH(&projection, 0.f, GAME_WIDTH, GAME_HEIGHT, 0.f, -1, 1);
	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
}

TextureTest1::~TextureTest1()
{
	SafeDelete(pPlanet);
}

bool TextureTest1::Init()
{
	return true;
}

void TextureTest1::Update()
{

}

void TextureTest1::Render()
{
	pTexture->Render();
	pPlanet->Render();
}
