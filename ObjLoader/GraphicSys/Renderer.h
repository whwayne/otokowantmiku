#pragma once
#include "D3D9Device.h"
#include "../MikuCore/Ptr.h"



class Renderable;

class Renderer
{
public:
	Renderer();
	virtual ~Renderer();


	virtual void Render(Renderable& rdable);


protected:
private:
};