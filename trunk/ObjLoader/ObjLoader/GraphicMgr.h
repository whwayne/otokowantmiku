#pragma once
#include "Memory.h"
#include "RenderPipeline.h"
#include "Renderer.h"
#include "CullSystem.h"
#include "matrix44.h"

class GraphicMgr
{
public:
	static GraphicMgr& GetInstance()
	{
		static GraphicMgr instance;
		return instance;
	} 

	virtual ~GraphicMgr();

	void Init();
	void OnFrame(float deltaTime);

	std::list<Ptr<Renderable>>& GetRenderableList(RenderType type)
	{
		return m_RenderableArries[type];
	}

	void AttachRenderable(Ptr<Renderable>& pRenderable);

	Renderer* GetRenderer()
	{
		return m_pRenderer;
	}

    void SetViewProj(const matrix44& vp)
	{
		m_viewProj = vp;
	}
protected:

	GraphicMgr();
	std::vector<std::list<Ptr<Renderable>>> m_RenderableArries;

	RenderPipeline* m_pPipeline;

	Renderer*       m_pRenderer;

	CullSystem*     m_pCullSystem;

	//Frustum         m_Frustum;
	matrix44        m_viewProj;
private:
};
