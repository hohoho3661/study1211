#pragma once
// GameSys.h : 시스템 헤더, 다이렉트X 관련 헤더..

#define WIN32_LEAN_AND_MEAN

// Win32 관련
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// C 런타임
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <tchar.h>
#include <time.h>
#include <math.h>

// C++ 런타임
#include <vector>
#include <string>
#include <map>

// DX 관련
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")