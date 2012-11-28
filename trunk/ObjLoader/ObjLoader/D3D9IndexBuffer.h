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
	virtual void Copy(D3D9Res& rhs)
	{
		D3D9IndexBuffer* ib = (D3D9IndexBuffer*)(&rhs);
		if (m_pD3D9IndexBuffer!=ib->m_pD3D9IndexBuffer)
		{
			if (m_pD3D9IndexBuffer)
			{
				m_pD3D9IndexBuffer->Release();
			}	
			m_pD3D9IndexBuffer = ib->m_pD3D9IndexBuffer;
			if (m_pD3D9IndexBuffer)
			{
				m_pD3D9IndexBuffer->AddRef();
			}
		}
	}

	IDirect3DIndexBuffer9* GetD3D9IndexBufferPtr()
	{
		return m_pD3D9IndexBuffer;
	}

	IDirect3DIndexBuffer9** GetD3D9IndexBufferPP()
	{
		return &m_pD3D9IndexBuffer;
	}
protected:
	IDirect3DIndexBuffer9*    m_pD3D9IndexBuffer;


};