#include "D3D9Mesh.h"


D3D9Mesh::D3D9Mesh()
	:m_pVBArray()
	,m_pIBArray()
{

}


D3D9Mesh::~D3D9Mesh()
{

}


bool D3D9Mesh::SetUpFromObjLoader( ObjLoader& objMesh )
{
	std::vector<ObjSubMeshContent>& content = objMesh.GetContent();

	if (content.size()==0)
	{
		return false;
	}

	for (int iSubMesh = 0; iSubMesh<content.size(); iSubMesh++)
	{
		Ptr<D3D9VertexBuffer> pVB = new D3D9VertexBuffer();
		Ptr<D3D9IndexBuffer> pIB = new D3D9IndexBuffer();


		int vertexCount = content[0].mVertexBuffer.size()/8;

		if( FAILED( D3D9Device::GetInstance().GetD3DDevice9()->CreateVertexBuffer(vertexCount*sizeof( CUSTOMVERTEX ),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT,pVB->GetD3D9VertexBufferPP(), NULL ) ) )
		{
			return false;
		}
		CUSTOMVERTEX* pVertices ;
		pVB->GetD3D9VertexBufferPtr()->Lock(0, 0, ( void** )&pVertices, 0 );
		memcpy(pVertices,&content[0].mVertexBuffer[0],vertexCount*sizeof( CUSTOMVERTEX ));
		pVB->GetD3D9VertexBufferPtr()->Unlock();


		if( FAILED( D3D9Device::GetInstance().GetD3DDevice9()->CreateIndexBuffer(content[0].mVertexIndexBuffer.size()*sizeof( int ),0,D3DFMT_INDEX32,D3DPOOL_DEFAULT,pIB->GetD3D9IndexBufferPP(),NULL ) ) )
		{
			return false;
		}

		int* pIndex ;
		pIB->GetD3D9IndexBufferPtr()->Lock(0, 0,( void** )&pIndex, 0 );
		memcpy(pIndex,&content[0].mVertexIndexBuffer[0],content[0].mVertexIndexBuffer.size()*sizeof( int ));
		pIB->GetD3D9IndexBufferPtr()->Unlock();

		m_pVBArray.push_back(pVB);
		m_pIBArray.push_back(pIB);
	}
	return true;
	
}
