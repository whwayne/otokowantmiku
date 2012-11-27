#pragma once
#include "D3D9Device.h"
#include "D3D9Res.h"

class D3D9VertexBuffer:public D3D9Res
{
public:
	D3D9VertexBuffer();
	virtual ~D3D9VertexBuffer();

public:

	virtual void Copy(D3D9Res& rhs)
	{
		//m_pD3D9VertexBuffer->AddRef();
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