#include "D3D9Texture.h"
#include "d3d9.h"
#include "D3D9Device.h"
#include "TexLoader.h"
#include "UtilTex.h"

#include <d3dx9.h>

D3D9Texture::D3D9Texture()
{

}
D3D9Texture::~D3D9Texture()
{

}
bool D3D9Texture::SetUp(Loader& loader)
{
	HRESULT hr = D3DXCreateTextureFromFile(D3D9Device::GetInstance().GetD3DDevice9(),"cup.jpg",&m_pD3D9Texture);
	if (hr!=S_OK)
	{
		return false;
	}
	return true;

// 	TexLoader& texLoader = (TexLoader&)loader;
// 	IDirect3DDevice9* device = D3D9Device::GetInstance().GetD3DDevice9();
// 	DDSTexDataInfo* textureInfo = texLoader.GetTexDataInfo();
// 	D3DFORMAT fmt = GetD3D9Format( textureInfo->mDDS_HEADER->ddspf );
// 	HRESULT hr = device->CreateTexture( textureInfo->mDDS_HEADER->dwWidth,
// 	 textureInfo->mDDS_HEADER->dwHeight,
// 	 textureInfo->mDDS_HEADER->dwMipMapCount,
// 	 D3DUSAGE_DYNAMIC, // usage
// 	 fmt,
// 	 D3DPOOL_MANAGED,
// 	 &m_pD3D9Texture,
// 	 NULL );
// 	if(hr == S_OK)
// 	{
// 
// 		D3DLOCKED_RECT d3dlr;
// 		hr = m_pD3D9Texture->LockRect(0,&d3dlr,NULL,0 );
// 		if ( hr!=S_OK)
// 		{
// 			return false;
// 		}
// 		memcpy(d3dlr.pBits,texLoader.GetTexDataInfo()->mTexData,texLoader.GetTexDataInfo()->mTexDataSize);
// 		m_pD3D9Texture->UnlockRect(0);
// 		return true;
// 	}
// 	else
// 	{
// 		return false;
// 	}


}

IDirect3DTexture9* D3D9Texture::GetD3D9TexturePtr()
{
    return m_pD3D9Texture;
}
