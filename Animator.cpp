#include "GameSys.h"
#include "User.h"
#include "Animator.h"

Animator::Animator(std::vector<AnimationClip>* srcClips, Type type)
{
	repeatType = type;
	curClipNumber = 0;
	isPlay = false;
	isReverse = false;

	for (auto& a : *srcClips)			// for each�� �������°� auto ������ ���� �����ؿ��°ǵ�,,,,,, ���������ϰ������ ���۷��������� ���亯���� ������
	{
		a.time = a.time < 100 ? 100 : a.time; // ���׿���      ?     �� : ����
		clips.push_back(a);
	}
}

Animator::~Animator()
{
}

void Animator::Update()
{
	if (!isPlay)
		return;

	AnimationClip clip = clips[curClipNumber];

	if (timeGetTime() - playTime > clip.time)
	{
		switch (repeatType)
		{
		case Type::END:
			curClipNumber++;
			if (curClipNumber >= clips.size())
				Stop();
			break;
		case Type::LOOP:
			curClipNumber++;
			curClipNumber %= clips.size();
			break;
		case Type::PINGPONG:
			if (isReverse)
			{
				curClipNumber--;
				if (curClipNumber <= 0)
					isReverse = false;
			}
			else
			{
				curClipNumber++;
				if (curClipNumber >= clips.size() - 1)
					isReverse = true;
			}
			break;
		default:
			break;
		}

		playTime = timeGetTime();
	}
}

void Animator::Render()
{
	clips[curClipNumber].texture->Render();
}

void Animator::Play()
{
	isPlay = true;
	playTime = timeGetTime();
}

void Animator::Pause()
{
	isPlay = false;
}

void Animator::Stop()
{
	isPlay = false;
	curClipNumber = 0;
}
