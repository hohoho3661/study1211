#pragma once

class Planet
{
	Texture*	texture;

	D3DXVECTOR2	pos;
	D3DXVECTOR2	scale;

	float		angle;

	D3DXMATRIX	world;
	D3DXMATRIX*	matParent;

public:
	Planet(tstring fileName);
	~Planet();

	void SetPos(D3DXVECTOR2 _pos) { pos = _pos; }
	D3DXVECTOR2 GetPos() { return pos; }

	void SetScale(D3DXVECTOR2 _scale) { scale = _scale; }
	D3DXVECTOR2 GetScale() { return scale; }

	void SetParent(D3DXMATRIX* pMat) { matParent = pMat; }
	D3DXMATRIX* getWorld() { return &world; }


	void Update();
	void Render();
};

