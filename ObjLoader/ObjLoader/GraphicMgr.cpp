#include "GraphicMgr.h"
#include "FixedRenderPipeline.h"
#include "FixedRenderer.h"

GraphicMgr::GraphicMgr()
	:m_pPipeline(NULL)
	,m_pRenderer(NULL)
	,m_pCullSystem(NULL)
	,m_RenderableArries()
	,m_viewProj()
{

}

GraphicMgr::~GraphicMgr()
{
	if (m_pPipeline)
	{
		o_delete(m_pPipeline);
		m_pPipeline = NULL;
	}
	if (m_pRenderer)
	{
		o_delete(m_pRenderer);
		m_pRenderer = NULL;
	}
	if (m_pCullSystem)
	{
		o_delete(m_pCullSystem);
		m_pCullSystem = NULL;
	}
}

void GraphicMgr::Init()
{
	// here we will init the current pipeline and cull sys;
	m_pPipeline = o_new(FixedRenderPipeline);
	m_pPipeline->Init();

	m_pRenderer = o_new(FixedRenderer);//hack
	for (int i = 0;i<RENDERTYPECOUNT;i++)
	{
		m_RenderableArries.push_back(std::list<Ptr<Renderable>>());
	}


	// here we will setup the culling system
	m_pCullSystem = o_new(CullSystem);
	m_pCullSystem->SetDepth(3);
	aabbox cullArea;
	cullArea.SetMax(point( 500.f, 500.f, 500.f,1.f));
	cullArea.SetMin(point(-500.f,-500.f,-500.f,1.f));
	m_pCullSystem->SetCullArea(cullArea);
	m_pCullSystem->Init();

}

void GraphicMgr::OnFrame( float deltaTime )
{
	//do the culling and push the results to the pipeline and render.
	//- cull at first,now it's empty,because I haven't do it. 
	m_pCullSystem->Cull(m_viewProj,m_pCullSystem->GetRootNode(),m_pPipeline->GetRenderables());
	//- get the culling result, and render.
//  	m_pPipeline->GetRenderableList(COMMONTYPE) = m_RenderableArries[COMMONTYPE];
//  	m_pPipeline->GetRenderableList(ALPHABLEND) = m_RenderableArries[ALPHABLEND];
//  	m_pPipeline->GetRenderableList(ALPHATEST) = m_RenderableArries[ALPHATEST];

	m_pPipeline->RenderRenderables();
}

void GraphicMgr::AttachRenderable(const Ptr<Renderable>& pRenderable )
{
	GetRenderableList(pRenderable->GetRenderType()).push_back(pRenderable);
	m_pCullSystem->AttachRenderable(pRenderable);
}
