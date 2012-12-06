#pragma once

#include "D3D9Device.h"
#include "D3D9VertexBuffer.h"
#include "D3D9IndexBuffer.h"
#include "D3D9VertexLayout.h"
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

	void SetVertexLayout(Ptr<D3D9VertexLayout> pVL)
	{
		m_pVL = pVL;
	}

	Ptr<D3D9VertexBuffer> GetVertexBuffer()
	{
		return m_pVB;
	}

	Ptr<D3D9IndexBuffer> GetIndexBuffer()
	{
		return m_pIB;
	}

	Ptr<D3D9VertexLayout> GetVertexLayout()
	{
		return m_pVL;
	}

	void SetIndexCount(int count)
	{
		m_IndexCount = count;
	}
	int GetIndexCount()
	{
		return m_IndexCount;
	}

	void SetVertexCount(int count)
	{
		 m_VertexCount = count;
	}
	int GetVertexCount()
	{
		return m_VertexCount;
	}

	void Copy(D3D9Res& rhs);
protected:
	Ptr<D3D9VertexBuffer> m_pVB;
	Ptr<D3D9IndexBuffer>  m_pIB;
	Ptr<D3D9VertexLayout> m_pVL;

	int m_VertexCount;
	int m_IndexCount;
private:
};