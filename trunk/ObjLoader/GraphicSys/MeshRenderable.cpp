#include "MeshRenderable.h"

MeshRenderable::MeshRenderable()
	:m_pSubMesh()
{

}

MeshRenderable::~MeshRenderable()
{

}

aabbox MeshRenderable::GetWorldBBox()
{
	aabbox localBox = m_pSubMesh->GetVertexBuffer()->GetBBox();
	return localBox.Transform(m_World);
}

