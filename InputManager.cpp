#include "GameSys.h"
#include "User.h"


#include "InputManager.h"


InputManager* InputManager::instance = NULL;

InputManager::InputManager()
{
	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyOldState, sizeof(keyOldState));
	ZeroMemory(keyMap, sizeof(keyMap));
}


InputManager::~InputManager()
{
}

InputManager * InputManager::GetInstance()
{
	if (instance == 0)
		instance = new InputManager;

	return instance;
}

void InputManager::Update()
{
	memcpy(keyOldState, keyState, sizeof(keyOldState));

	ZeroMemory(keyState, sizeof(keyState));
	ZeroMemory(keyMap, sizeof(keyMap));

	GetKeyboardState(keyState);

	for (int i = 0; i < MAX_KEY; i++)
	{
		byte key = keyState[i] & 0x80;
		keyState[i] = key ? 1 : 0;

		int OldState = keyOldState[i];
		int state = keyState[i];

		if (OldState == 0 && state == 1)
			keyMap[i] = DOWN;

		else if (OldState == 1 && state == 0)
			keyMap[i] = UP;

		else if (OldState == 1 && state == 1)
			keyMap[i] = PRESS;
		else
			keyMap[i] = NONE;
	}
}

void InputManager::Release()
{
	if (instance)
	{
		delete instance;
		instance = 0;
	}
}
