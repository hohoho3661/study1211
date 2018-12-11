#pragma once

// 투영행렬 만드는 작업을 카메라가 해줌
class Camera 
{
	D3DXMATRIX	view;
	D3DXMATRIX	proj;
	
	D3DXVECTOR2	cameraPos;
	
public:
	Camera();
	~Camera();

	void Update();
	
	//void GetCamPos(D3DXVECTOR2* pos) { *pos = cameraPos; } // 겟함수 만드는 또다른 방법 : 보이드형이면 매개변수 *pos 를 받아오니까,,, 이런식으로도 구현가능.
	D3DXVECTOR2 GetCameraPos() { return cameraPos; }
	void SetCameraPos(D3DXVECTOR2 _pos) { cameraPos = _pos; }


	void SetProjection();

};

