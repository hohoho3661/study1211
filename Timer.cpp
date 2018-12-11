#include "GameSys.h"
#include "Timer.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib") // ��ũ�� �ַ�


Timer::Timer()
{
}


Timer::~Timer()
{
}

bool Timer::Init()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency)) // QueryPerformanceFrequency = cpu�� ���ư��� �ӵ�..?   // ���� ����
	{
		_isHardWare = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);

		_timeScale = 1.0f / _periodFrequency;
	}
	else																													// ������
	{
		_isHardWare = false;
		_lastTime = timeGetTime();
		_timeScale = 0.001f;
	}

	_frameRate = 0;
	_FPSframeCount = 0;
	_FPSTimeElapsed = 0.f;
	_worldTime = 0.f;

	return true;
}



// ���� fps��� : 1�ʿ� xx������.. �����ð��������θ� ����      0.01666�ʸ��� ȣ�� ..   
//				 1�ʿ� 60���� ȣ��ǰ� �Ұ���
//				 Ÿ�̸Ӷ� �����ؼ� �������� �����.

// ���� fps��� : ������ ��ŸŸ���� ������ ���Ƿ� �۾�..      ���°� ������ ������,, �������Ұ� �������� ������

void Timer::Tick(float lockFPS)    // ������Ʈ���� ��� ȣ��
{
	if (_isHardWare)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	}
	else
	{
		_curTime = timeGetTime();
	}

	_timeElapsed = (_curTime - _lastTime) * _timeScale; // Ÿ�ӽ������� �����༭ �ð��� ������. ex)60�� ���ϸ� 1��

	if (lockFPS > 0.0f)				// lockFPS�� �������ִٸ�.. �� ���� ������ ���̵�.
	{
		while (_timeElapsed < 1.0f / lockFPS) // 1.0 .. ũ�� ������    ������ ����
		{
			if (_isHardWare)
				QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			else
				_curTime = timeGetTime();

			_timeElapsed = (_curTime - _lastTime)* _timeScale;
		}
	}

	_lastTime = _curTime;
	_FPSframeCount++;
	_FPSTimeElapsed += _timeElapsed;
	_worldTime += _timeElapsed;

	if (_FPSTimeElapsed > 1.0f)
	{
		_frameRate = _FPSframeCount;
		_FPSframeCount = 0;
		_FPSTimeElapsed = 0.0f;
	}
}

unsigned long Timer::getFrameRate(TCHAR * str)
{
	if (str != NULL)
	{
		//_stprintf(str, TEXT("FPS : %d"), _frameRate);
	}

	return _frameRate;
}
