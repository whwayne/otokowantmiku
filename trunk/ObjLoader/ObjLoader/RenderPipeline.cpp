#include "RenderPipeline.h"


RenderPipeline::RenderPipeline()
{

}

RenderPipeline::~RenderPipeline()
{

}

void RenderPipeline::Init()
{
	for (int i = 0;i<RENDERTYPECOUNT;i++)
	{
		m_RenderableArries.push_back(std::list<Ptr<Renderable>>());
	}
}

