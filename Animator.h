#pragma once

enum Type
{
	END,
	LOOP,
	PINGPONG,
};

struct AnimationClip
{
	Texture*	texture;
	DWORD		time;

	AnimationClip()
	{
		texture = nullptr;
		time = 0;
	}
	AnimationClip(Texture* _texture, DWORD _time)
	{
		texture = _texture;
		time = _time;
	}
};

class Animator
{
	std::vector<AnimationClip> clips;

	Type	repeatType;

	DWORD	playTime;
	UINT	curClipNumber;

	bool	isPlay;
	bool	isReverse;

public:
	Animator(std::vector<AnimationClip>* srcClips, Type type = Type::END);
	~Animator();

	void Update();
	void Render();
	void Play();
	void Pause();
	void Stop();

	void SetClipInit() { curClipNumber = 0; }
	Texture* GetTexture() { return clips[curClipNumber].texture; }
	UINT		GetCurrentClipNumber() { return curClipNumber; }
};

// �ؽ��� �ϳ��� ���� - �ִϸ��̼� Ŭ��
// �� Ŭ������ �𿩼� �ִϸ��̼��� �������
