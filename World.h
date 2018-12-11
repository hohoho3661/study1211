#pragma once

// 어떤 객체가 월드내에 표시되기 위해 필요한 정보
// 


class World
{	
	D3DXMATRIX	matWorld; // 월드행렬을 만들고

	D3DXVECTOR2	pos;	// 포지션
	D3DXVECTOR2	scale;
	D3DXVECTOR3	rot;

	D3DXVECTOR2	size;

	D3DXVECTOR2	pivot;

	// 충돌 관련 처리를 위해 추가
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

	// AABB 충돌
	//bool IsAABBCollision(const World& _world) const;
	bool IsCollision(World* _world);
};

// Box의 충돌처리
// 1. AABB (Axis Aligned Boundary Box)
//    Box의 축이 좌표계와 평행인 상태가 불변.
// 2. OBB (Oriented Boundary Box)
//    축과 정렬 상태를 보장하지 않음. 회전이 가능

// 로직자체는 똑같음. 사용되는 자료형만 다름.
// 여기서는 Vector를 사용하고 float타입을 사용.




//struct AABB	// 정렬된 축을 기준으로 하는 박스 (Axis Aligned Boundary Box),,,, 충돌체 자체가 회전하지 않는다를 전제로
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
//	float radius; // 반지름
//	D3DXVECTOR2	pos;
//};
//
//float GetDistance(D3DXVECTOR2 a, D3DXVECTOR2 b)
//{
//	return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
//	// sqrtf는 제곱근 구하는 함수
//}
//
//bool IsCircleCollision(const Circle& a, const Circle& b )
//{
//	float r = a.radius + b.radius;
//	return r < GetDistance(a.pos, b.pos);
//}