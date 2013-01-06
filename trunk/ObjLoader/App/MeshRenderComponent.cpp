#include "MeshRenderComponent.h"
#include "..\MikuCore\ResourceMgr.h"
#include "..\GraphicSys\GraphicMgr.h"

namespace FrameWork
{

	MeshRenderComponent::MeshRenderComponent()
		:m_pD3D9Mesh(0)
		,m_arrRenderable()
		,m_MeshID()
	{

	}

	MeshRenderComponent::~MeshRenderComponent()
	{

	}

	void MeshRenderComponent::SetMeshID( const std::string& meshID )
	{
		m_arrRenderable.clear();
		m_pD3D9Mesh = NULL;
		m_MeshID = meshID;

		m_pD3D9Mesh = (D3D9Mesh*)ResourceMgr::GetInstance().GetResAnsycByID<ObjLoader,D3D9Mesh>(m_MeshID).get();
	}

	void MeshRenderComponent::OnFrame( float deltaTime )
	{
		if (!m_pD3D9Mesh)
		{
			return;
		}
		if (m_pD3D9Mesh->GetSubMeshCount()>0&&m_arrRenderable.size()==0) // loading complete,then create
		{
			for (int i = 0;i<m_pD3D9Mesh->GetSubMeshCount();i++)
			{
				MeshRenderable* pMeshRenderable = new MeshRenderable();
				pMeshRenderable->SetRender(GraphicMgr::GetInstance().GetRenderer());
				pMeshRenderable->SetSubMesh( m_pD3D9Mesh->GetSubMeshArray()[i] );
				pMeshRenderable->SetRenderType(COMMONTYPE);

				GraphicMgr::GetInstance().AttachRenderable( Ptr<Renderable>(pMeshRenderable) );
				m_arrRenderable.push_back( Ptr<Renderable>(pMeshRenderable) );
			}
		}
	}

}