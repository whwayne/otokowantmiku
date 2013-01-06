#pragma once
#include "Component.h"
#include "..\ScriptFeature\ScriptInstance.h"
#include <vector>

namespace FrameWork
{
	class LogicComponent:public Component
	{
		__DeclareClass(LogicComponent)
	public:
		LogicComponent();
		virtual ~LogicComponent();

		virtual void OnFrame(float deltaTime);
		void AddScriptInstance(Ptr<App::ScriptInstance>& scriptInstance);
	protected:
		std::vector<Ptr<App::ScriptInstance>> m_arrScriptInstances;

	};
}