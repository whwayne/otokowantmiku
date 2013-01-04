#include "FixedRenderPipeline.h"



void FixedRenderPipeline::RenderRenderables()
{

	// now only render the COMMONTYPE list;
	std::list<Ptr<Renderable>>& renderableList = GetRenderableList(COMMONTYPE);
	std::list<Ptr<Renderable>>::iterator rdableiter  = renderableList.begin();
	for (;rdableiter!=renderableList.end(); rdableiter++ )
	{
		(*rdableiter)->GetRenderer()->Render(*(*rdableiter).get());
	}

}
