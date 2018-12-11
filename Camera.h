#pragma once

// ������� ����� �۾��� ī�޶� ����
class Camera 
{
	D3DXMATRIX	view;
	D3DXMATRIX	proj;
	
	D3DXVECTOR2	cameraPos;
	
public:
	Camera();
	~Camera();

	void Update();
	
	//void GetCamPos(D3DXVECTOR2* pos) { *pos = cameraPos; } // ���Լ� ����� �Ǵٸ� ��� : ���̵����̸� �Ű����� *pos �� �޾ƿ��ϱ�,,, �̷������ε� ��������.
	D3DXVECTOR2 GetCameraPos() { return cameraPos; }
	void SetCameraPos(D3DXVECTOR2 _pos) { cameraPos = _pos; }


	void SetProjection();

};

