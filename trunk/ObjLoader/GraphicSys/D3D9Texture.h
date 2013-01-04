#pragma once
#include "D3D9Device.h"
#include "D3D9Res.h"
#include "../MikuCore/Loader.h"

class D3D9Texture : public D3D9Res
{
public:
	D3D9Texture();
	~D3D9Texture();
	virtual bool SetUp(Loader& loader);
	IDirect3DTexture9* GetD3D9TexturePtr();
protected:
	IDirect3DTexture9* m_pD3D9Texture;
private:
};