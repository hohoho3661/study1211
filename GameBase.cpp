#include "GameSys.h"
#include "User.h"

#include "GameBase.h"


GameBase::GameBase()
{
	bInit = false;
}

GameBase::~GameBase()
{
	DeleteAll();
	ShowCursor(true);
}

LRESULT GameBase::MsgHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) // 마우스 포인터 위치를 설정해주는 함수   ( 메세지 설정 )
{
	if (bInit)
	{
		switch (msg)
		{
		case WM_MOUSEMOVE:
			mousePos.x = static_cast<float>(LOWORD(lParam));
			mousePos.y = static_cast<float>(HIWORD(lParam));
			break;
		}

	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void GameBase::Init(HWND hWnd)
{
	GRAPHICS->Init(hWnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);
	
//	pGraphics->SetBackColor(0xffff00ff);

	bInit = true;
}

void GameBase::Run(HWND)
{
	if (GRAPHICS == NULL)
		return;

	Update();
	RenderGame();
}

void GameBase::RenderGame()
{
	if (SUCCEEDED(GRAPHICS->BeginScene()))
	{
		Render();
		GRAPHICS->EndScene();
	}

	HandleLostGraphicsDevice();

	GRAPHICS->ShowBackBuffer();
}

void GameBase::HandleLostGraphicsDevice()
{
	result = GRAPHICS->GetDeviceState();
	if (FAILED(result))
	{
		if (result == D3DERR_DEVICELOST) // 디바이스를 잃어버리면
		{
			Sleep(100);					// 0.1초 기다렷다가 리턴
			return;
		}
		else if (result == D3DERR_DEVICENOTRESET)	// 디바이스를 리셋할수 없는상태면
		{
			ReleaseAll();							// 객체들을 다 지우고
			result = GRAPHICS->Reset();
			if (FAILED(result))
				return;

			ResetAll();
		}
		else
			return;
	}
}


void GameBase::ReleaseAll()
{
}

void GameBase::ResetAll()
{
}

void GameBase::DeleteAll()
{
	ReleaseAll();
//	SafeRelease(GRAPHICS);
	bInit = false;
}