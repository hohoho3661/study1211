#pragma once

// � ��ü�� ���峻�� ǥ�õǱ� ���� �ʿ��� ����
// 


class World
{	
	D3DXMATRIX	matWorld; // ��������� �����

	D3DXVECTOR2	pos;	// ������
	D3DXVECTOR2	scale;
	D3DXVECTOR3	rot;

	D3DXVECTOR2	size;

	D3DXVECTOR2	pivot;

	// �浹 ���� ó���� ���� �߰�
	D3DXVECTOR2	minBox;
	D3DXVECTOR2	maxBox;

public:
	World();
	~World();

	void Update();

	D3DXVECTOR2 GetPosition() const { return pos; }
	D3DXVECTOR2 GetScale() const { return scale; }
	D3DXVECTOR3 GetRotation() const { return rot; }
	D3DXVECTOR2* GetSize() { return &size; }


	void SetPosition(D3DXVECTOR2 _pos) { pos = _pos; }
	void SetScale(D3DXVECTOR2 _scale) { scale = _scale; }
	void SetRotation(D3DXVECTOR3 _rot) { rot = _rot; }

	void SetSize(D3DXVECTOR2 _size) { size = _size; }
	void SetPivot(D3DXVECTOR2 _pivot) { pivot = _pivot; }


	void SetWorld();


	void SetBox();
	void GetBox(D3DXVECTOR2* min, D3DXVECTOR2* max);

	// AABB �浹
	//bool IsAABBCollision(const World& _world) const;
	bool IsCollision(World* _world);
};

// Box�� �浹ó��
// 1. AABB (Axis Aligned Boundary Box)
//    Box�� ���� ��ǥ��� ������ ���°� �Һ�.
// 2. OBB (Oriented Boundary Box)
//    ��� ���� ���¸� �������� ����. ȸ���� ����

// ������ü�� �Ȱ���. ���Ǵ� �ڷ����� �ٸ�.
// ���⼭�� Vector�� ����ϰ� floatŸ���� ���.




//struct AABB	// ���ĵ� ���� �������� �ϴ� �ڽ� (Axis Aligned Boundary Box),,,, �浹ü ��ü�� ȸ������ �ʴ´ٸ� ������
//{
//	D3DXVECTOR2	minBox;	// left top
//	D3DXVECTOR2	maxBox;	// right bottom
//};
//bool IsAABBCollision(AABB& _box)
//{
//	if (colBox.maxBox.x < _box.minBox.x || colBox.minBox.x > _box.maxBox.x)
//	{
//		return false;
//	}
//	if (colBox.maxBox.y < _box.minBox.y || colBox.minBox.y > _box.maxBox.y)
//	{
//		return false;
//	}
//	return true;
//}

//struct Circle
//{
//	float radius; // ������
//	D3DXVECTOR2	pos;
//};
//
//float GetDistance(D3DXVECTOR2 a, D3DXVECTOR2 b)
//{
//	return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
//	// sqrtf�� ������ ���ϴ� �Լ�
//}
//
//bool IsCircleCollision(const Circle& a, const Circle& b )
//{
//	float r = a.radius + b.radius;
//	return r < GetDistance(a.pos, b.pos);
//}