#pragma once

#include "D3D9Device.h"
#include "D3D9VertexBuffer.h"
#include "D3D9IndexBuffer.h"
#include "ObjLoader.h"
#include "Ptr.h"
#include <vector>

class D3D9Mesh:public D3D9Res
{
public:
	D3D9Mesh();
	virtual ~D3D9Mesh();

	
	virtual bool SetUp(Loader& loader);

	std::vector< Ptr<D3D9VertexBuffer> >& GetVBArray()
	{
		return m_pVBArray;
	}

	std::vector< Ptr<D3D9IndexBuffer> >& GetIBArray()
	{
		return m_pIBArray;
	}

protected:
	std::vector<Ptr<D3D9VertexBuffer>> m_pVBArray;
	std::vector<Ptr<D3D9IndexBuffer>>  m_pIBArray;

private:
};