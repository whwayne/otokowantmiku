#pragma once
#include "Renderable.h"
#include "Renderer.h"
#include "../MikuCore/Ptr.h"
#include <vector>
#include <list>

class RenderPipeline
{
public:
	RenderPipeline();
	virtual ~RenderPipeline();

	virtual void Init();

	std::list<Ptr<Renderable>>& GetRenderableList(RenderType type)
	{
		return m_RenderableArries[type];
	}

	std::vector<std::list<Ptr<Renderable>>>& GetRenderables()
	{
		return m_RenderableArries;
	}

	virtual void RenderRenderables();

protected:
	std::vector<std::list<Ptr<Renderable>>> m_RenderableArries;
private:
};