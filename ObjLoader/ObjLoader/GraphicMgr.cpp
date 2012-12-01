#include "GraphicMgr.h"
#include "FixedRenderPipeline.h"

GraphicMgr::GraphicMgr()
	:m_pPipeline(NULL)
	,m_RenderableArries()
{

}

GraphicMgr::~GraphicMgr()
{
	if (m_pPipeline)
	{
		delete m_pPipeline;
	}
}

void GraphicMgr::Init()
{
	// here we will init the current pipeline and cull sys;
	m_pPipeline = new FixedRenderPipeline();
	m_pPipeline->Init();
	for (int i = 0;i<RENDERTYPECOUNT;i++)
	{
		m_RenderableArries.push_back(std::list<Ptr<Renderable>>());
	}
}

void GraphicMgr::OnFrame( float deltaTime )
{
	//do the culling and push the results to the pipeline and render.
	//- cull at first,now it's empty,because I haven't do it. 

	//- get the culling result, and render.
	m_pPipeline->GetRenderableList(COMMONTYPE) = m_RenderableArries[COMMONTYPE];
	m_pPipeline->GetRenderableList(ALPHABLEND) = m_RenderableArries[ALPHABLEND];
	m_pPipeline->GetRenderableList(ALPHATEST) = m_RenderableArries[ALPHATEST];

	m_pPipeline->RenderRenderables();
}
