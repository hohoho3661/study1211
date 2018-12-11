#include "GameSys.h"
#include "User.h"
#include "Scene.h"
#include "Graphics.h"
#include "SRTTest.h"

// 행렬의 곱은 교환법칙이 성립안함.

SRTTest::SRTTest()
{
	scaling = { 1, 1 }; // 0은 0,,, 1은 100퍼센트    ,,스케일에 관련된 초기화는 기본이 1로 초기화한다.
	rotation = { 0, 0, 0 };
	translation = { 0, 0 };

}

SRTTest::~SRTTest()
{
}

bool SRTTest::Init(Graphics * _pGraphics)
{
	if (_pGraphics)
		pGraphics = _pGraphics;
	else
		return false;

	UINT vertexCount = 3;

	Vertex* vertex = new Vertex[vertexCount];
	vertex[0] = Vertex(50, 0, 0xffff0000);
	vertex[1] = Vertex(100, 50 * tanf(D3DX_PI / 3), 0xff0000ff);
	vertex[2] = Vertex(0, 50* tanf(D3DX_PI /3), 0xff00ff00);

	UINT vertexSize = sizeof(Vertex)* vertexCount;

	HRESULT result = DEVICE->CreateVertexBuffer(vertexSize,
		0, Vertex::fvf, D3DPOOL_DEFAULT, &vertexBuffer, NULL);

	if (FAILED(result))
		return false;

	void* vertexData = NULL;

	// 0부터 버텍스사이즈만큼 버택스버퍼를 통해 읽어온다.
	result = vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	if (FAILED(result))
		return false;

	// 버텍스버퍼에 ,,,,,  만들어논 버텍스 정보를 카피하는것
	memcpy(vertexData, vertex, vertexSize);

	vertexBuffer->Unlock();

	delete[] vertex;

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	float fWidth = (float)viewport.Width;
	float fHeight = (float)viewport.Height;

		
	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, fWidth, fHeight, 0.0f, -1, 1);   // 레프트, 라이트, 바텀, 탑 , 해당영역에 대한 직교투영

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);


	DEVICE->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); // 뒷면을 그려줌.
	DEVICE->SetRenderState(D3DRS_LIGHTING, FALSE);



	// 항등행렬을 만들어서 초기화한다.
	D3DXMatrixIdentity(&world);


	return true;
}

void SRTTest::Update()
{
	if (INPUT->KeyPress(VK_RIGHT))
	{
		translation.x++;
	}
	if (INPUT->KeyPress(VK_LEFT))
	{
		translation.x--;
	}
	if (INPUT->KeyPress(VK_UP))
	{
		translation.y--;
	}
	if (INPUT->KeyPress(VK_DOWN))
	{
		translation.y++;
	}

	D3DXMATRIX center, invCenter; // 행렬과 그 행렬의 역행렬을 만들어놈

	//  행렬              역행렬
	// 이동행렬          마이너스
	// 회전행렬            역수
	// 로테이션행렬      전체행렬

	D3DXMatrixTranslation(&center, 50, 50, 0);
	D3DXMatrixInverse(&invCenter, NULL, &center);

	D3DXMATRIX T;
	D3DXMatrixTranslation(&T, translation.x, translation.y, 0); // T( Translation )매트릭스를 생성
	
	if (INPUT->KeyPress('W'))
	{
		scaling.y += 0.1f;
	}
	if (INPUT->KeyPress('S'))
	{
		scaling.y -= 0.1f;
	}
	if (INPUT->KeyPress('A'))
	{
		scaling.x -= 0.1f;
	}
	if (INPUT->KeyPress('D'))
	{
		scaling.x += 0.1f;
	}

	D3DXMATRIX S, matS;
	D3DXMatrixScaling(&matS, scaling.x, scaling.y, 1); // 스케일에 관련된 초기화는 기본이 1로 초기화한다.

	S = invCenter * matS * center; //

	if (INPUT->KeyPress('I'))
	{
		rotation.z += 0.1f;
	}
	if (INPUT->KeyPress('K'))
	{
		rotation.z -= 0.1f;
	}

	D3DXMATRIX R, matR;
	D3DXMatrixRotationZ(&matR, rotation.z);

	R = invCenter * matR * center; // 역행렬에 변환행렬을 곱해서 만들어줌

	world = S * R * T;	// 순서 중요 ( 행렬의 곱은 교환법칙이 성립안함 )
	
}

void SRTTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf); // 버텍스포맷 세팅하고
	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));// 어디서 읽어올것인지 정보를 세팅
	DEVICE->SetTransform(D3DTS_WORLD, &world); // 만든 월드행렬을 랜더링 파이프라인에 적용
	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1); // 그려준다
}
