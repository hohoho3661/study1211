#pragma once


class GameBase
{
protected:

	HWND		hWnd;
	HRESULT		result;

	bool		bInit;

public:
	GameBase();
	virtual ~GameBase();

	LRESULT		MsgHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	virtual void Init(HWND hWnd);
	
	virtual void Run(HWND);
	
	virtual void ReleaseAll();
	
	virtual void ResetAll();

	virtual void DeleteAll();

	virtual void RenderGame();

	virtual void HandleLostGraphicsDevice();


	void ExitGame() { PostMessage(hWnd, WM_DESTROY, 0, 0); }

	virtual void Update() = 0; // 순수 가상 함수,,			 추상클래스,, 단독으로 객체를 만들수 없다 ( 객체화 할수 없는 클래스 )
	virtual void Render() = 0;


};