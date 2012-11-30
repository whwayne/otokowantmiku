#pragma once
#include "Renderer.h"
#include "Renderable.h"
#include "D3D9SubMesh.h"


// mesh that can be rendered,now there is only a mesh here,later we may put the materail info here too.

class MeshRenderable:public Renderable
{
public:
	MeshRenderable();
	virtual ~MeshRenderable();

	void SetSubMesh(Ptr<D3D9SubMesh> pSubMesh)
	{
		m_pSubMesh = pSubMesh;
	}
	Ptr<D3D9SubMesh> GetSubMesh()
	{
		return m_pSubMesh;
	}
protected:
	Ptr<D3D9SubMesh> m_pSubMesh;
	
};