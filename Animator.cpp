#include "GameSys.h"
#include "User.h"
#include "Animator.h"

Animator::Animator(std::vector<AnimationClip>* srcClips, Type type)
{
	repeatType = type;
	curClipNumber = 0;
	isPlay = false;
	isReverse = false;

	for (auto& a : *srcClips)			// for each로 루프도는건 auto 변수를 만들어서 복사해오는건데,,,,,, 직접수정하고싶으면 레퍼런스형으로 오토변수를 만들면됨
	{
		a.time = a.time < 100 ? 100 : a.time; // 삼항연산      ?     참 : 거짓
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
