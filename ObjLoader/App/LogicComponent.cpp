#include "LogicComponent.h"

namespace FrameWork
{
	__ImplementClass(LogicComponent,'LGCM',Component)

	LogicComponent::LogicComponent()
	:m_arrScriptInstances()
	{

	}

	LogicComponent::~LogicComponent()
	{

	}

	void LogicComponent::AddScriptInstance( Ptr<App::ScriptInstance>& scriptInstance )
	{
		m_arrScriptInstances.push_back(scriptInstance);
	}

	void LogicComponent::OnFrame( float deltaTime )
	{
		for (int i =0 ;i<m_arrScriptInstances.size();i++)
		{
			m_arrScriptInstances[i]->OnFrame();
		}
	}

}