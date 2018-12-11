#pragma once
// Constants.h : 프로젝트 내부에서 사용되는 상수, 매크로 열거자 ....

#define Win32_LEAN_AND_MEAN

const char CLASS_NAME[] = "WinMain";
const char GAME_TITLE[] = "DirectX";

const bool FULLSCREEN = false;

const size_t GAME_WIDTH = 1000;
const size_t GAME_HEIGHT = 700;


// Safely Delete Pointer

template <typename T>
inline void SafeRelease(T& p) // 다이렉트로 만들어지는 객체는 delete하면 안된다. release할것!
{
	if (p)
	{
		p->Release();		
		p = NULL;
	}
}
#define SAFE_RELEASE SafeRelease

template <typename T>
inline void SafeDelete(T& p)
{
	if (p)
	{
		delete p;
		p = NULL;
	}
}
#define SAFE_DELETE SafeDelete

template <typename T>
inline void SafeDeleteArray(T& p)
{
	if (p)
	{
		delete [] p;
		p = NULL;
	}
}
#define SAFE_DELETE_ARRAY SafeDeleteArray

// TString
#if defined(_UNICODE) || defined(UNICODE)
typedef std::wstring	tstring;
#else
typedef std::string		tstring;
#endif // #ifdef _UNICODE