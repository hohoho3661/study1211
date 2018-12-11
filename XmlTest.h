#pragma once

class Player;
class MyObject;

class XmlTest : public Scene
{
	Player*		player;
	MyObject*	obj;
public:
	XmlTest();
	~XmlTest();

	bool Init();
	void Update();
	void Render();
};

