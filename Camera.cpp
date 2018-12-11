#include "GameSys.h"
#include "User.h"

#include "Camera.h"


Camera::Camera()
{
	cameraPos = { 0, 0 };
	D3DXMatrixTranslation(&view, cameraPos.x, cameraPos.y, 0);
	SetProjection();
}


Camera::~Camera()
{
}

void Camera::Update()
{
	if (KEYPRESS(VK_CONTROL))
	{
		if (KEYPRESS(VK_RIGHT))
			cameraPos.x++;
		if (KEYPRESS(VK_LEFT))
			cameraPos.x--;
		if (KEYPRESS(VK_UP))
			cameraPos.y--;
		if (KEYPRESS(VK_DOWN))
			cameraPos.y++;
	}



	D3DXMatrixTranslation(&view, cameraPos.x, cameraPos.y, 0);
	DEVICE->SetTransform(D3DTS_VIEW, &view);
}

void Camera::SetProjection()
{
	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	float fWidth = (float)viewport.Width;
	float fHeight = (float)viewport.Height;

	D3DXMatrixOrthoOffCenterLH(&proj, 0.0f, fWidth, fHeight, 0.0f, -1, 1);

	DEVICE->SetTransform(D3DTS_PROJECTION, &proj);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
}
