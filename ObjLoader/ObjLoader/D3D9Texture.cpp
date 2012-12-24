#include "D3D9Texture.h"
#include "d3d9.h"
#include "D3D9Device.h"
#include "TexLoader.h"
#include "UtilTex.h"

D3D9Texture::D3D9Texture()
{

}
D3D9Texture::~D3D9Texture()
{

}
bool D3D9Texture::SetUp(Loader& loader)
{

 	TexLoader& texLoader = (TexLoader&)loader;
 	IDirect3DDevice9* device = D3D9Device::GetInstance().GetD3DDevice9();
 	DDSTexDataInfo* textureInfo = texLoader.GetTexDataInfo();
	DDS_HEADER* ddsHeader = textureInfo->mDDS_HEADER;
 	D3DFORMAT fmt = GetD3D9Format( textureInfo->mDDS_HEADER->ddspf );

	HRESULT hr = S_OK;
    D3DLOCKED_RECT LockedRect = {0};

	UINT iWidth =ddsHeader->dwWidth;
    UINT iHeight = ddsHeader->dwHeight;
    UINT iMipCount = ddsHeader->dwMipMapCount;
    if( 0 == iMipCount )
        iMipCount = 1;

    if (ddsHeader->dwCubemapFlags != 0
        || (ddsHeader->dwHeaderFlags & DDS_HEADER_FLAGS_VOLUME) )
    {
        // For now only support 2D textures, not cubemaps or volumes
        return E_FAIL;
    }


    // Create the texture
    LPDIRECT3DTEXTURE9 pTexture;
    LPDIRECT3DTEXTURE9 pStagingTexture;
    hr = device->CreateTexture( iWidth,
                              iHeight,
                              iMipCount,
                              0, // usage
                              fmt,
                              D3DPOOL_DEFAULT,
                              &pTexture,
                              NULL );
    if( FAILED( hr ) )
        return hr;

    hr = device->CreateTexture( iWidth,
                              iHeight,
                              iMipCount,
                              0, // usage
                              fmt,
                              D3DPOOL_SYSTEMMEM,
                              &pStagingTexture,
                              NULL );
    if( FAILED( hr ) )
    {
        return hr;
    }

    // Lock, fill, unlock
    UINT RowBytes, NumRows;
	BYTE* pSrcBits = textureInfo->mTexData;

    for( UINT i = 0; i < iMipCount; i++ )
    {
        GetSurfaceInfo( iWidth, iHeight, fmt, NULL, &RowBytes, &NumRows );

        if( SUCCEEDED( pStagingTexture->LockRect( i, &LockedRect, NULL, 0 ) ) )
        {
            BYTE* pDestBits = ( BYTE* )LockedRect.pBits;

            // Copy stride line by line
            for( UINT h = 0; h < NumRows; h++ )
            {
                CopyMemory( pDestBits, pSrcBits, RowBytes );
                pDestBits += LockedRect.Pitch;
                pSrcBits += RowBytes;
            }

            pStagingTexture->UnlockRect( i );
        }

        iWidth = iWidth >> 1;
        iHeight = iHeight >> 1;
        if( iWidth == 0 )
            iWidth = 1;
        if( iHeight == 0 )
            iHeight = 1;
    }

    hr = device->UpdateTexture( pStagingTexture, pTexture );
    if( FAILED( hr ) )
        return hr;

    // Set the result
    m_pD3D9Texture = pTexture;
    return hr;


}

IDirect3DTexture9* D3D9Texture::GetD3D9TexturePtr()
{
    return m_pD3D9Texture;
}

