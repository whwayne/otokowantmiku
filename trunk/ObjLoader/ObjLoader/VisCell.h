#pragma once
#include <vector>
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
	std::vector<Ptr<Renderable>>& GetRenderables()
	{
		return mRenderables;
	}

	aabbox& GetAABB()
	{
		return cellBox;
	}
protected:
	aabbox cellBox;
	std::vector<Ptr<Renderable>> mRenderables;

protected:
	
	
private:
};