#pragma once

#include "D3D9Device.h"
#include "D3D9VertexBuffer.h"
#include "D3D9IndexBuffer.h"
#include "ObjLoader.h"
#include "Ptr.h"

class D3D9SubMesh:public D3D9Res
{
public:
	D3D9SubMesh();
	virtual ~D3D9SubMesh();

	void SetVertexBuffer(Ptr<D3D9VertexBuffer> pVB)
	{
		m_pVB = pVB;
	}

	void SetIndexBuffer(Ptr<D3D9IndexBuffer> pIB)
	{
		m_pIB = pIB;
	}

	Ptr<D3D9VertexBuffer> GetVertexBuffer()
	{
		return m_pVB;
	}

	Ptr<D3D9IndexBuffer> GetIndexBuffer()
	{
		return m_pIB;
	}

protected:
	Ptr<D3D9VertexBuffer> m_pVB;
	Ptr<D3D9IndexBuffer>  m_pIB;

private:
};