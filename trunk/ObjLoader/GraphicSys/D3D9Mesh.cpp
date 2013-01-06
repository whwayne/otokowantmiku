#include "D3D9Mesh.h"


D3D9Mesh::D3D9Mesh()
    :m_pSubMeshPtrArray(NULL)
	,m_SubMeshCount(0)
{

}


D3D9Mesh::~D3D9Mesh()
{
	if (m_pSubMeshPtrArray)
	{
		o_deleteArray(m_pSubMeshPtrArray);
	}
}


bool D3D9Mesh::SetUp(Loader& loader)
{
	ObjLoader* pLoader = (ObjLoader*)(&loader);

	std::vector<ObjSubMeshContent>& content = pLoader->GetContent();

	if (content.size()==0)
	{
		return false;
	}
	m_SubMeshCount = content.size();

	m_pSubMeshPtrArray = o_newArray(Ptr<D3D9SubMesh>,m_SubMeshCount);


	for (int iSubMesh = 0; iSubMesh<m_SubMeshCount; iSubMesh++)
	{
		Ptr<D3D9VertexBuffer> pVB = o_new( D3D9VertexBuffer);
		Ptr<D3D9IndexBuffer> pIB = o_new( D3D9IndexBuffer);
		Ptr<D3D9VertexLayout> pVL = o_new( D3D9VertexLayout);

		Ptr<D3D9SubMesh> pSubMesh = o_new( D3D9SubMesh);
		int vertexCount = content[iSubMesh].mVertexBuffer.size()/8;
		//VERTEX BUFFER
		if( FAILED( D3D9Device::GetInstance().GetD3DDevice9()->CreateVertexBuffer(vertexCount*sizeof( CUSTOMVERTEX ),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT,pVB->GetD3D9VertexBufferPP(), NULL ) ) )
		{
			return false;
		}
		CUSTOMVERTEX* pVertices ;
		pVB->GetD3D9VertexBufferPtr()->Lock(0, 0, ( void** )&pVertices, 0 );
		memcpy(pVertices,&content[iSubMesh].mVertexBuffer[0],vertexCount*sizeof( CUSTOMVERTEX ));
		pVB->GetD3D9VertexBufferPtr()->Unlock();

		//INDEX BUFFER
		if( FAILED( D3D9Device::GetInstance().GetD3DDevice9()->CreateIndexBuffer(content[iSubMesh].mVertexIndexBuffer.size()*sizeof( int ),0,D3DFMT_INDEX32,D3DPOOL_DEFAULT,pIB->GetD3D9IndexBufferPP(),NULL ) ) )
		{
			return false;
		}
		int* pIndex ;
		pIB->GetD3D9IndexBufferPtr()->Lock(0, 0,( void** )&pIndex, 0 );
		memcpy(pIndex,&content[iSubMesh].mVertexIndexBuffer[0],content[iSubMesh].mVertexIndexBuffer.size()*sizeof( int ));
		pIB->GetD3D9IndexBufferPtr()->Unlock();

		//VERTEX LAYOUT
		for (unsigned int i = 0;i<content[iSubMesh].mVertexLayout.size();i++)
		{
			D3D9VertexComponent com(content[iSubMesh].mVertexLayout[i]);
			pVL->AddComponent(com);
		}
		pVL->SetUp();

		//LOCAL BOUNDING BOX
		pVB->SetBBox( CaculateSubMeshBBox(content[iSubMesh].mVertexBuffer));         

		pSubMesh->SetIndexBuffer(pIB);
		pSubMesh->SetVertexBuffer(pVB);
		pSubMesh->SetVertexLayout(pVL);
		pSubMesh->SetIndexCount(content[iSubMesh].mVertexIndexBuffer.size()/3);
		pSubMesh->SetVertexCount(vertexCount);
		m_pSubMeshPtrArray[iSubMesh] = pSubMesh;
		
	}
	return true;
	
}

void D3D9Mesh::Copy( HardwareRes& rhs )
{
	D3D9Mesh* pSource = (D3D9Mesh*)(&rhs);
	this->m_SubMeshCount = pSource->m_SubMeshCount;
	this->m_pSubMeshPtrArray = pSource->m_pSubMeshPtrArray;
}

aabbox D3D9Mesh::CaculateSubMeshBBox(std::vector<float>& vertices )
{
	aabbox bbox;
	bbox.GetMax() = float4(vertices[0],vertices[1],vertices[2],1.f);
	bbox.GetMin() = float4(vertices[0],vertices[1],vertices[2],1.f);

	for (unsigned int i = 0;i<vertices.size();i = i+3)
	{
		bbox.GetMax().X() = Max(bbox.GetMax().X(),vertices[i]);
		bbox.GetMin().X() = Min(bbox.GetMin().X(),vertices[i]);

		bbox.GetMax().Y() = Max(bbox.GetMax().Y(),vertices[i]);
		bbox.GetMin().Y() = Min(bbox.GetMin().Y(),vertices[i]);

		bbox.GetMax().Z() = Max(bbox.GetMax().Z(),vertices[i]);
		bbox.GetMin().Z() = Min(bbox.GetMin().Z(),vertices[i]);
	}

	return bbox;
}
