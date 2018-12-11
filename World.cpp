#include "GameSys.h"
#include "User.h"
#include "World.h"

World::World()
{
	scale	= { 1, 1 };
	rot		= { 0, 0, 0 };
	pos		= { 0, 0 };

	pivot	= { 0, 0 };
	size	= { 0, 0 };

	minBox = { 0, 0 };
	maxBox = { 0, 0 };
	
	D3DXMatrixIdentity(&matWorld); // ��������� �׵������ ���� �ʱ�ȭ�Ѵ�.
}

World::~World()
{
}

void World::Update()
{
	D3DXMATRIX	P, IP;
	D3DXMATRIX	S, R, T;
	D3DXMATRIX	matS, matR;

	D3DXMatrixTranslation(&P, pivot.x, pivot.y, 0);
	D3DXMatrixInverse(&IP, NULL, &P);

	D3DXMatrixScaling(&matS, scale.x, scale.y, 1);

	S = IP * matS * P;

	D3DXMatrixRotationYawPitchRoll(&matR, rot.y, rot.x, rot.z); // �Ѳ����� �����̼��ϴ� �Լ�,,  y, x, z ����                  0,1,0�� ��溤�ͷ� ������ �ϴ��� ����
	R = IP * matR * P;

	D3DXMatrixTranslation(&T, pos.x, pos.y, 0);

	matWorld = S * R * T;
}

void World::SetWorld()
{
	DEVICE->SetTransform(D3DTS_WORLD, &matWorld); // ������ ���� ����
}

void World::SetBox()
{
	minBox = pos - size * GetScale().x * 0.5;
	maxBox = pos + size * GetScale().y * 0.5;
}

void World::GetBox(D3DXVECTOR2 * min, D3DXVECTOR2 * max)
{
	*min = minBox;
	*max = maxBox;
}

bool World::IsCollision(World * _world)
{
	// ���� �������δ� �浹 ���ιۿ� �Ǻ��� ����
	// �󸶳� �浹�ߴ����� �˷��� �� vector������ ���� ���̸� �˾Ƴ��� ��

	SetBox();
	_world->SetBox();

	D3DXVECTOR2 min = { 0, 0 };
	D3DXVECTOR2 max = { 0, 0 };

	_world->GetBox(&min, &max);

	if (maxBox.x < min.x || minBox.x > max.x)
	{
		return false;
	}
	if (maxBox.y < min.y || minBox.y > max.y)
	{
		return false;
	}
	return true;
}

//bool World::IsAABBCollision(const World & _world) const
//{
//	if (maxBox.x < _world.minBox.x || minBox.x > _world.maxBox.x)
//	{
//		return false;
//	}
//	if (maxBox.y < _world.minBox.y || minBox.y > _world.maxBox.y)
//	{
//		return false;
//	}
//	return true;
//}

