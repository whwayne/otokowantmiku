#include "D3D9Mesh.h"


D3D9Mesh::D3D9Mesh()
	:m_pSubMeshArray()
{

}


D3D9Mesh::~D3D9Mesh()
{

}


bool D3D9Mesh::SetUp(Loader& loader)
{
	ObjLoader* pLoader = (ObjLoader*)(&loader);

	std::vector<ObjSubMeshContent>& content = pLoader->GetContent();

	if (content.size()==0)
	{
		return false;
	}

	for (int iSubMesh = 0; iSubMesh<content.size(); iSubMesh++)
	{
		Ptr<D3D9VertexBuffer> pVB = o_new( D3D9VertexBuffer);
		Ptr<D3D9IndexBuffer> pIB = o_new( D3D9IndexBuffer);

		Ptr<D3D9SubMesh> pSubMesh = o_new( D3D9SubMesh);
		int vertexCount = content[iSubMesh].mVertexBuffer.size()/8;

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


		if( FAILED( D3D9Device::GetInstance().GetD3DDevice9()->CreateIndexBuffer(content[iSubMesh].mVertexIndexBuffer.size()*sizeof( int ),0,D3DFMT_INDEX32,D3DPOOL_DEFAULT,pIB->GetD3D9IndexBufferPP(),NULL ) ) )
		{
			return false;
		}

		int* pIndex ;
		pIB->GetD3D9IndexBufferPtr()->Lock(0, 0,( void** )&pIndex, 0 );
		memcpy(pIndex,&content[iSubMesh].mVertexIndexBuffer[0],content[iSubMesh].mVertexIndexBuffer.size()*sizeof( int ));
		pIB->GetD3D9IndexBufferPtr()->Unlock();

		pSubMesh->SetIndexBuffer(pIB);
		pSubMesh->SetVertexBuffer(pVB);
		pSubMesh->SetIndexCount(content[iSubMesh].mVertexIndexBuffer.size()/3);
		pSubMesh->SetVertexCount(vertexCount);
		m_pSubMeshArray.push_back(pSubMesh);
	}
	return true;
	
}
