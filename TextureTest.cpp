#include "GameSys.h"
#include "User.h"
#include "Scene.h"

#include "TextureTest.h"



TextureTest::TextureTest()
{
	//// 다이렉트에서는 이미지를 출력하기전에 보정작업을 위해 이미지사이즈를 2의 제곱수로 표시되는걸 원칙으로함.
	//D3DXCreateTextureFromFile(DEVICE, TEXT("Image/rocket.png"), &texture);
	
	// 좀더 컨트롤하기 용이한 함수를 사용해서 문제를 해결한다.
	D3DXCreateTextureFromFileEx(
		DEVICE,
		TEXT("Image/rocket.png"),
		D3DX_DEFAULT_NONPOW2,	// 2의 n승으로 사이즈처리를 하지않겟다.
		D3DX_DEFAULT_NONPOW2,
		1, // 크면 로드할때 오래걸림 (미리만들어놓고 처리하는 거)
		NULL,
		D3DFMT_UNKNOWN, // D3DFMT_A8B8G8R8 이런식으로 명시해도됨.
		D3DPOOL_DEFAULT,
		D3DX_FILTER_NONE,
		D3DX_FILTER_NONE,
		RGB(255, 0, 255),	// 삭제할 배경
		NULL,
		NULL,
		&texture
	);



	// 이미지 정보를 알아서 이미지크기에 맞춰보자
	D3DSURFACE_DESC decs;	// 만들고
	texture->GetLevelDesc(0, &decs); // 담는다.

	vertexCount = 6;
	vertex = new Vertex[vertexCount];
	//vertex[0] = Vertex(0, 0, 0, 0 );
	//vertex[1] = Vertex(400, 0, 1, 0 );
	//vertex[2] = Vertex(0, 400, 0, 1 );
	//vertex[3] = Vertex(0, 400, 0, 1 );
	//vertex[4] = Vertex(400, 0, 1, 0 );
	//vertex[5] = Vertex(400, 400, 1, 1 );
	vertex[0] = Vertex(0, 0, 0, 0);				
	vertex[1] = Vertex(decs.Width, 0, 1, 0);
	vertex[2] = Vertex(0, decs.Height, 0, 1);
	vertex[3] = Vertex(0, decs.Height, 0, 1);
	vertex[4] = Vertex(decs.Width, 0, 1, 0);
	vertex[5] = Vertex(decs.Width, decs.Height, 1, 1);

	D3DVIEWPORT9 viewport;
	DEVICE->GetViewport(&viewport);

	D3DXMatrixOrthoOffCenterLH(&projection, 0.f, (float)viewport.Width, (float)viewport.Height, 0.f, -1, 1);

	DEVICE->SetTransform(D3DTS_PROJECTION, &projection);
	DEVICE->SetRenderState(D3DRS_LIGHTING, false);
}


TextureTest::~TextureTest()
{
	texture->Release();
}

bool TextureTest::Init()
{
	return true;
}

void TextureTest::Update()
{
}

void TextureTest::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetTexture(0, texture);

	// 알파 블랜딩

	// 알파 연산의 시작
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	
	// 알파 연산 방법 설정
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); // 덧셈연산을 하겟다는 뜻

	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	DEVICE->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, vertex, sizeof(Vertex));

	// 알파 연산의 끝
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
