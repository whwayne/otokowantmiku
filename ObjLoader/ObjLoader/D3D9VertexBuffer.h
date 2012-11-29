#pragma once
#include "D3D9Device.h"
#include "D3D9Res.h"


// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	FLOAT x, y, z; // The transformed position for the vertex
	FLOAT nx,ny,nz;
	FLOAT u,v;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX0|D3DFVF_NORMAL)




class D3D9VertexBuffer:public D3D9Res
{
public:
	D3D9VertexBuffer();
	virtual ~D3D9VertexBuffer();

public:
	virtual bool SetUp(Loader& loader);

	virtual void Copy(D3D9Res& rhs)
	{
		D3D9VertexBuffer* vb = (D3D9VertexBuffer*)(&rhs);
		if (m_pD3D9VertexBuffer!=vb->m_pD3D9VertexBuffer)
		{
			if (m_pD3D9VertexBuffer!=NULL)
			{
				m_pD3D9VertexBuffer->Release();
			}
			m_pD3D9VertexBuffer = vb->m_pD3D9VertexBuffer;
			if (m_pD3D9VertexBuffer)
			{
				m_pD3D9VertexBuffer->AddRef();
			}
		}
	}
	
	
	IDirect3DVertexBuffer9* GetD3D9VertexBufferPtr()
	{
		return m_pD3D9VertexBuffer;
	}

	IDirect3DVertexBuffer9** GetD3D9VertexBufferPP()
	{
		return &m_pD3D9VertexBuffer;
	}
protected:
	IDirect3DVertexBuffer9*    m_pD3D9VertexBuffer;


};