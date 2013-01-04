#include "D3D9IndexBuffer.h"

D3D9IndexBuffer::D3D9IndexBuffer()
	:m_pD3D9IndexBuffer(NULL)
{

}

D3D9IndexBuffer::~D3D9IndexBuffer()
{
	if (m_pD3D9IndexBuffer)
	{
		m_pD3D9IndexBuffer->Release();
	}
}

bool D3D9IndexBuffer::SetUp( Loader& loader )
{
	return false;
}
