#include "GameSys.h"
#include "User.h"
#include "Graphics.h"

Graphics::Graphics()
{
	direct3D = NULL;
	device3D = NULL;
	fullScreen = false;
	width = GAME_WIDTH;
	height = GAME_HEIGHT;
	backColor = SETCOLOR_AGRB(255, 128, 128, 128);
}

Graphics::~Graphics()
{
	ReleaseAll();
}

void Graphics::Init(HWND _hWnd, int _width, int _height, bool _fullScreen)
{
	hWnd = _hWnd;
	width = _width;
	height = _height;
	fullScreen = _fullScreen;

	direct3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (direct3D == NULL)
		throw(GameError(GE_NS::FATAL_ERROR, "Error Initializing Direct3D."));

	InitD3DPP();

	if (fullScreen)
	{
		if (isAdapterCompatible())
			d3dpp.FullScreen_RefreshRateInHz = pMode.RefreshRate;
		else
			throw(GameError(GE_NS::FATAL_ERROR, 
				"The Graphics device does not support the specified resolution ans/or format."));
	}

	D3DCAPS9	caps;
	DWORD		behavior;

	result = direct3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	if ((caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) == 0 ||
		caps.VertexShaderVersion < D3DVS_VERSION(1, 1))
		behavior = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	else
		behavior = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	result = direct3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		behavior,
		&d3dpp,
		&device3D);

	if(FAILED(result))
		throw(GameError(GE_NS::FATAL_ERROR, "Error Creating Direct3D Device."));
}

void Graphics::InitD3DPP()
{
	try
	{
		ZeroMemory(&d3dpp, sizeof(d3dpp));

		d3dpp.BackBufferWidth = width;
		d3dpp.BackBufferHeight = height;
		if (fullScreen)
			d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
		else
			d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
		d3dpp.BackBufferCount = 1;
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.hDeviceWindow = hWnd;
		d3dpp.Windowed = (!fullScreen);

		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}
	catch (...)
	{
		throw(GameError(GE_NS::FATAL_ERROR, "Error Initializing D3D Presentation Parameter."));
	}
}

void Graphics::ReleaseAll()
{
	SafeRelease(device3D);
	SafeRelease(direct3D);
}

HRESULT Graphics::ShowBackBuffer()
{
	result = E_FAIL;
//	device3D->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 255, 0), 0.0f, 0);
	result = device3D->Present(NULL, NULL, NULL, NULL);
	return result;
}

bool Graphics::isAdapterCompatible()
{
	UINT modes = direct3D->GetAdapterModeCount(D3DADAPTER_DEFAULT,
		d3dpp.BackBufferFormat);
	for (UINT i = 0; i < modes; i++)
	{
		result = direct3D->EnumAdapterModes(D3DADAPTER_DEFAULT,
			d3dpp.BackBufferFormat, i, &pMode);
		if (pMode.Height == d3dpp.BackBufferHeight &&
			pMode.Width == d3dpp.BackBufferWidth &&
			pMode.RefreshRate == d3dpp.FullScreen_RefreshRateInHz)
			return true;
	}

	return false;
}

HRESULT Graphics::Reset()
{
	InitD3DPP();
	result = device3D->Reset(&d3dpp);
	return result;
}

HRESULT Graphics::GetDeviceState()
{
	result = E_FAIL;
	if (device3D == NULL)
		return result;

	result = device3D->TestCooperativeLevel();
	return result;
}

HRESULT Graphics::BeginScene()
{
	result = E_FAIL;
	if (device3D == NULL)
		return result;

	device3D->Clear(0, NULL, D3DCLEAR_TARGET, backColor, 1.0f, 0);
	
	result = device3D->BeginScene();

	return result;
}

HRESULT Graphics::EndScene()
{
	result = E_FAIL;
	if (device3D)
		result = device3D->EndScene();
	
	return result;
}