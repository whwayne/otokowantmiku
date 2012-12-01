#pragma once
#include "RenderPipeline.h"

class GraphicMgr
{
public:
	static GraphicMgr& GetInstance()
	{
		static GraphicMgr instance;
		return instance;
	} 

	virtual ~GraphicMgr();

	void Init();
	void OnFrame(float deltaTime);

	std::list<Ptr<Renderable>>& GetRenderableList(RenderType type)
	{
		return m_RenderableArries[type];
	}

protected:

	GraphicMgr();
	std::vector<std::list<Ptr<Renderable>>> m_RenderableArries;

	RenderPipeline* m_pPipeline;
private:
};
