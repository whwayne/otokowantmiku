#include "ScriptInstance.h"
#include "ScriptManager.h"
#include "ScriptUtitly.h"
#include "ScriptClass.h"

namespace App
{
	ScriptInstance::ScriptInstance()
		:m_pScriptClass(0)
	{
		for ( int i=0;i<ScriptInstance::MethodCount;i++)
		{
			m_pEntryMethods[i] = NULL;
		}
	}

	ScriptInstance::~ScriptInstance()
	{

	}
	void ScriptInstance::Init( MonoImage* pImage,const char* cclass )
	{
		CppObjToScriptObj(*this,cclass);
		m_pScriptClass = ScriptGeneralManager::GetInstance().GetScriptClass(cclass);
		GetMethods(m_pScriptClass->GetMonoClass());
	}

	void ScriptInstance::OnFrame()
	{
		mono_runtime_invoke(m_pEntryMethods[ScriptInstance::MethodOnFrame],GetMonoObj(),NULL,NULL);
	}

	void ScriptInstance::GetMethods(MonoClass* pClass)
	{
		for (int i=0;i<ScriptInstance::MethodCount;i++)
		{
			m_pEntryMethods[i] = m_pScriptClass->GetMethod(scEntryMethodNames[i]);
			
			if ( m_pEntryMethods[i]==NULL )
			{
				MonoClass* pParentClass = mono_class_get_parent( m_pScriptClass->GetMonoClass() );
				GetMethods(pParentClass);
			}
		}
		
	}

}