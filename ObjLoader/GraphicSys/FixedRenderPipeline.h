#pragma once
#include "RenderPipeline.h"

class FixedRenderPipeline:public RenderPipeline
{
public:
	FixedRenderPipeline(){}
	virtual ~FixedRenderPipeline(){}

	virtual void RenderRenderables();
	
protected:
private:
};