#pragma once
#include "Renderable.h"
#include "Renderer.h"
#include "Ptr.h"
#include <vector>
#include <list>

enum RenderType
{
	COMMONTYPE = 0,
	ALPHABLEND = 1,
	ALPHATEST  = 2,
	RENDERTYPECOUNT,
};

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
protected:
	std::vector<std::list<Ptr<Renderable>>> m_RenderableArries;
private:
};