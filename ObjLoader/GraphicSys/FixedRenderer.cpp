#include "FixedRenderer.h"
#include "MeshRenderable.h"

FixedRenderer::FixedRenderer()
{
	
}

FixedRenderer::~FixedRenderer()
{

}



void FixedRenderer::Render( Renderable& rdable )
{
	Ptr<MeshRenderable> pMesh =(MeshRenderable*) (&rdable);

	const matrix44* pM44 = & rdable.GetWorld();


	D3D9Device::GetInstance().GetD3DDevice9()->SetTransform( D3DTS_WORLD , (D3DXMATRIX*)pM44 );
	D3D9Device::GetInstance().GetD3DDevice9()->SetIndices(pMesh->GetSubMesh()->GetIndexBuffer()->GetD3D9IndexBufferPtr());
	D3D9Device::GetInstance().GetD3DDevice9()->SetStreamSource( 0, pMesh->GetSubMesh()->GetVertexBuffer()->GetD3D9VertexBufferPtr(), 0, sizeof( CUSTOMVERTEX ) );
	D3D9Device::GetInstance().GetD3DDevice9()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,pMesh->GetSubMesh()->GetVertexCount(),0,pMesh->GetSubMesh()->GetIndexCount());

	D3D9Device::GetInstance().GetD3DDevice9()->SetVertexDeclaration(pMesh->GetSubMesh()->GetVertexLayout()->GetD3D9VertexDeclarationPtr());

}
