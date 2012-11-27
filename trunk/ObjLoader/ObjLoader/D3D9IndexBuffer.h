#pragma once
#include "D3D9Device.h"
#include "D3D9Res.h"
#include "Ptr.h"



class D3D9IndexBuffer:public D3D9Res
{
public:
	D3D9IndexBuffer();
	virtual ~D3D9IndexBuffer();

public:


	IDirect3DIndexBuffer9* GetD3D9VertexBufferPtr()
	{
		return m_pD3D9IndexBuffer;
	}

	IDirect3DIndexBuffer9** GetD3D9VertexBufferPP()
	{
		return &m_pD3D9IndexBuffer;
	}
protected:
	IDirect3DIndexBuffer9*    m_pD3D9IndexBuffer;


};