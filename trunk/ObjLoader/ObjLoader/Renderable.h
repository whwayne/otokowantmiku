#pragma once
#include "Ptr.h"
#include "Res.h"
#include "Renderer.h"

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


protected:
	Renderer*  m_pRenderer;


private:
};