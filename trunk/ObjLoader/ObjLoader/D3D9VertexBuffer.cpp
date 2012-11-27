#include "D3D9VertexBuffer.h"

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
