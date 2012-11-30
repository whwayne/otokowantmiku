#pragma once
#include "Renderer.h"
#include <vector>

class MeshRenderable;

class FixedRenderer:public Renderer
{
public:
	FixedRenderer();
	virtual ~FixedRenderer();
	virtual void Render(Renderable& rdable);
protected:
	
private:
};