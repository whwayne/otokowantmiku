#include "D3D9SubMesh.h"

D3D9SubMesh::D3D9SubMesh()
	:m_pVB(NULL)
	,m_pIB(NULL)
{

}

D3D9SubMesh::~D3D9SubMesh()
{

}

void D3D9SubMesh::Copy( D3D9Res& rhs )
{
// 	D3D9SubMesh* pSource = (D3D9SubMesh*)(&rhs);
// 	this->m_IndexCount = pSource->m_IndexCount;
// 	this->m_VertexCount= pSource->m_VertexCount;
// 	this->m_pIB->Copy(pSource->m_pIB);
// 	this->m_pVB->Copy(pSource->m_pVB);
}
