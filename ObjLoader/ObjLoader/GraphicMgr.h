#pragma once
#include "Memory.h"
#include "RenderPipeline.h"
#include "Renderer.h"
#include "CullSystem.h"


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
	Renderer* GetRenderer()
	{
		return m_pRenderer;
	}
protected:

	GraphicMgr();
	std::vector<std::list<Ptr<Renderable>>> m_RenderableArries;

	RenderPipeline* m_pPipeline;

	Renderer*       m_pRenderer;

	CullSystem*     m_pCullSystem;
private:
};
