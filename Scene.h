#pragma once

class Graphics;

class Scene
{
protected:
	Graphics*			pGraphics;

public:
	virtual bool Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};