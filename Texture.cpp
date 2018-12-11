#include "GameSys.h"
#include "User.h"
#include "Texture.h"

LPDIRECT3DVERTEXBUFFER9 Texture::vertexBuffer = NULL;
std::vector<Texture*> Texture::textures;
std::map<tstring, LPDIRECT3DTEXTURE9> Texture::textureMap;

Texture::Texture(LPDIRECT3DTEXTURE9 texture, D3DXVECTOR2 cutStart, D3DXVECTOR2 cutEnd)
{
	this->texture = texture;

	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);

	textureSize.x = static_cast<float>(desc.Width);
	textureSize.y = static_cast<float>(desc.Height);

	uvStart.x = cutStart.x / textureSize.x;
	uvStart.y = cutStart.y / textureSize.y;
	uvEnd.x = (cutEnd.x > 0) ? cutEnd.x / textureSize.x : 1.0f;
	uvEnd.y = (cutEnd.y > 0) ? cutEnd.y / textureSize.y : 1.0f;

	this->cutStart = cutStart;
	this->cutEnd.x = (cutEnd.x < 1) ? textureSize.x : cutEnd.x;
	this->cutEnd.y = (cutEnd.y < 1) ? textureSize.y : cutEnd.y;
}

Texture::~Texture()
{
}

void Texture::CreateVertexBuffer()
{
	SafeRelease(vertexBuffer);

	UINT vertexCount = textures.size() * 6;
	UINT vertexSize = vertexCount * sizeof(Vertex);

	DEVICE->CreateVertexBuffer(vertexSize, 0, Vertex::fvf, D3DPOOL_DEFAULT, &vertexBuffer, NULL);

	Vertex* vertex = new Vertex[vertexCount];
	for (size_t i = 0; i < textures.size(); ++i)
	{
		D3DXVECTOR2 size;
		textures[i]->GetRealSize(&size);


		D3DXVECTOR2 start = textures[i]->uvStart;
		D3DXVECTOR2 end = textures[i]->uvEnd;

		//vertex[i * 6 + 0] = Vertex(0, 0, start.x, start.y);	// 피벗( Pivot ) 위치가 left, top인 버텍스
		//vertex[i * 6 + 1] = Vertex(size.x, 0, end.x, start.y);
		//vertex[i * 6 + 2] = Vertex(0, size.y, start.x, end.y);
		//vertex[i * 6 + 3] = Vertex(0, size.y, start.x, end.y);
		//vertex[i * 6 + 4] = Vertex(size.x, 0, end.x, start.y);
		//vertex[i * 6 + 5] = Vertex(size.x, size.y, end.x, end.y);
		
		D3DXVECTOR2 halfsize = size * 0.5f;

		vertex[i * 6 + 0] = Vertex(-halfsize.x, -halfsize.y, start.x, start.y);	// 피벗위치가 센터인 버텍스
		vertex[i * 6 + 1] = Vertex(halfsize.x, -halfsize.y, end.x, start.y);
		vertex[i * 6 + 2] = Vertex(-halfsize.x, halfsize.y, start.x, end.y);
		vertex[i * 6 + 3] = Vertex(-halfsize.x, halfsize.y, start.x, end.y);
		vertex[i * 6 + 4] = Vertex(halfsize.x, -halfsize.y, end.x, start.y);
		vertex[i * 6 + 5] = Vertex(halfsize.x, halfsize.y, end.x, end.y);
	}

	void* vertexData = NULL;
	vertexBuffer->Lock(0, vertexSize, &vertexData, NULL);
	memcpy(vertexData, vertex, vertexSize);
	vertexBuffer->Unlock();

	delete[] vertex;
}

void Texture::ReleaseInstance()
{
	SafeRelease(vertexBuffer);

	for (auto a : textures)
		delete a;

	for (auto a : textureMap)
		a.second->Release();
}

Texture* Texture::Add(tstring fileName, D3DXVECTOR2 cutStart, D3DXVECTOR2 cutEnd)
{
	LPDIRECT3DTEXTURE9 dxTexture;

	// 이터레이터로 find()를 사용하는 방법이 정석
	if (textureMap.count(fileName) < 1)
	{
		D3DXCreateTextureFromFileEx(
			DEVICE,
			fileName.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			1,
			NULL,
			D3DFMT_UNKNOWN,
			D3DPOOL_DEFAULT,
			D3DX_FILTER_NONE,
			D3DX_FILTER_NONE,
			0xffff00ff,
			NULL,
			NULL,
			&dxTexture);

		textureMap.insert({ fileName, dxTexture });

	}
	else
	{
		dxTexture = textureMap[fileName];
	}

	Texture* texture = new Texture(dxTexture, cutStart, cutEnd);
	texture->number = textures.size();
	textures.push_back(texture);

	CreateVertexBuffer();

	return texture;
}

void Texture::Render()
{
	DEVICE->SetFVF(Vertex::fvf);
	DEVICE->SetTexture(0, texture);
	DEVICE->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));

	
	//알파 블랜딩
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	
	DEVICE->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); // 덧셈 연산을 하겠다는 뜻

	DEVICE->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DEVICE->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	DEVICE->DrawPrimitive(D3DPT_TRIANGLELIST, number * 6, 2);
	
	DEVICE->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}
