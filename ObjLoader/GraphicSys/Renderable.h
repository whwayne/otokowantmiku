#pragma once
#include "../MikuCore/Ptr.h"
#include "../MikuCore/Res.h"
#include "Renderer.h"
#include "../Util/AABBox.h"
#include "D3D9SubMesh.h"
#include "../Util/Matrix44.h"

enum RenderType
{
	COMMONTYPE = 0,
	ALPHABLEND = 1,
	ALPHATEST  = 2,
	RENDERTYPECOUNT,
};

//-parent class of all objs that can be rendered
class Renderable:public Res
{
public:
	Renderable();
	virtual ~Renderable();

	void SetRender(Renderer* pRenderer)
	{
		m_pRenderer = pRenderer;
	}


	Renderer* GetRenderer()
	{
		return m_pRenderer;
	}

	void SetRenderType(RenderType type)
	{
		m_RenderType = type;
	}

	RenderType GetRenderType()
	{
		return m_RenderType;
	}

	virtual Ptr<D3D9SubMesh> GetSubMesh() = 0;

	virtual aabbox GetWorldBBox() = 0;
	
	void SetWorld(const matrix44& mw)
	{
		m_World = mw;
	}

	const matrix44& GetWorld() const
	{
		return m_World;
	}
protected:
	matrix44   m_World;
	Renderer*  m_pRenderer;
	RenderType m_RenderType;
private:
};