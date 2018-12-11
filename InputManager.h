#pragma once

#define MAX_KEY 255

class InputManager
{
private:
	enum KeyState
	{
		NONE,
		DOWN,
		UP,
		PRESS,
	};

	byte keyState[MAX_KEY];
	byte keyOldState[MAX_KEY];
	byte keyMap[MAX_KEY];

	static InputManager* instance;
	
	InputManager();
	~InputManager();
public:
	static InputManager* GetInstance();

	void Update();
	void Release();

	bool KeyDown(DWORD key) { return keyMap[key] == DOWN; }
	bool KeyUp(DWORD key) { return keyMap[key] == UP; }
	bool KeyPress(DWORD key) { return keyMap[key] == PRESS; }
};

