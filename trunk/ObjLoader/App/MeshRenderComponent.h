#pragma 
#include "Component.h"
#include "..\GraphicSys\MeshRenderable.h"
#include "..\GraphicSys\D3D9Mesh.h"
#include <string>

namespace FrameWork
{
	class MeshRenderComponent: public Component
	{
	public:
		MeshRenderComponent();
		virtual ~MeshRenderComponent();

		virtual void OnFrame(float deltaTime);
		void SetMeshID(const std::string& meshID);

	protected:
		std::vector<Ptr<Renderable>> m_arrRenderable;
		std::string m_MeshID;
		D3D9Mesh*   m_pD3D9Mesh;
	private:
	};
}