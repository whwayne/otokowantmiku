#include "D3D9VertexBuffer.h"
#include "ObjLoader.h"

D3D9VertexBuffer::D3D9VertexBuffer()
	:m_pD3D9VertexBuffer(NULL)
{

}

D3D9VertexBuffer::~D3D9VertexBuffer()
{
	if (m_pD3D9VertexBuffer!=NULL)
	{
		m_pD3D9VertexBuffer->Release();
	}
}

bool D3D9VertexBuffer::SetUp( Loader& loader )
{
	return false;
}
