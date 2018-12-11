#pragma once
// User : 사용자 정의 헤더
#include "GameError.h"
#include "Constants.h"
#include "SingleTon.h"
#include "Scene.h"
#include "Texture.h"

#include "Graphics.h"

#include "InputManager.h"
#include "Timer.h"

#include "Xml.h"

//
#define GRAPHICS	Graphics::getSingleton()
#define DEVICE		Graphics::getSingleton()->get3DDevice()
#define INPUT		InputManager::GetInstance()
#define KEYDOWN(k)	INPUT->KeyDown(k)
#define KEYUP(k)	INPUT->KeyUp(k)
#define KEYPRESS(k)	INPUT->KeyPress(k)



// extern 변수
extern D3DXVECTOR2 mousePos;