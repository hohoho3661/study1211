#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#define D3D_DEBUG_INFO
#endif// #ifdef _DEBUG

#include "Constants.h"
#include "GameError.h"

#include "SingleTon.h"

#define COLOR_ARGB DWORD
#define SETCOLOR_AGRB(a, r, g, b) \
		((COLOR_ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16))|(((g)&0xff)<<8)|(((b)&0xff)))

class Graphics : public SingletonBase<Graphics>
{
private:
	LPDIRECT3D9				direct3D;
	LPDIRECT3DDEVICE9		device3D;
	D3DPRESENT_PARAMETERS	d3dpp;
	D3DDISPLAYMODE			pMode;

	HRESULT					result;
	HWND					hWnd;

	bool					fullScreen;

	int						width;
	int						height;

	COLOR_ARGB				backColor;

	void					InitD3DPP();
public:
	Graphics();
	~Graphics();

	void				Init(HWND _hWnd, int _width, int _height, bool _fullScreen);
	void				ReleaseAll();
	
	HRESULT				ShowBackBuffer();

	bool				isAdapterCompatible();
	
	// == 11.15
	HRESULT				Reset();

	LPDIRECT3D9			get3D() { return direct3D; }
	LPDIRECT3DDEVICE9	get3DDevice() { return device3D; }

	HDC					getDC() { return GetDC(hWnd); }

	HRESULT				GetDeviceState();

	void				SetBackColor(COLOR_ARGB c) { backColor = c; }

	HRESULT				BeginScene();
	HRESULT				EndScene();
};