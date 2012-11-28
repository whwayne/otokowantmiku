#include "D3D9VertexLayout.h"

D3D9VertexLayout::D3D9VertexLayout()
	:m_pVertexDeclaration(NULL)
{

}

D3D9VertexLayout::~D3D9VertexLayout()
{
	if (m_pVertexDeclaration)
	{
		m_pVertexDeclaration->Release();
	}
}
