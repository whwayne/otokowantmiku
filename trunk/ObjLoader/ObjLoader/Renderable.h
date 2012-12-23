#pragma once
#include "Ptr.h"
#include "Res.h"
#include "Renderer.h"
#include "AABBox.h"

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

	aabbox& GetBBox()
	{
		return m_BBox;
	}
	void SetBBox(aabbox& box)
	{
		m_BBox = box;
	}
protected:
	Renderer*  m_pRenderer;
	
	aabbox     m_BBox;
private:
};