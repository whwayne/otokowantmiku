#pragma once
#include <list>
#include "Ptr.h"
#include "AABBox.h"
#include "Renderable.h"

class VisCell
{
public:
	VisCell();
	virtual ~VisCell();

	void Init(int depth,int index);
public:
	std::list<Ptr<Renderable>>& GetRenderables()
	{
		return mRenderables;
	}

	void SetAABB(aabbox& box)
	{
		cellBox = box;
	}

	aabbox& GetAABB()
	{
		return cellBox;
	}
protected:
	aabbox cellBox;
	std::list<Ptr<Renderable>> mRenderables;

protected:
	
	
private:
};