#include "ScriptInstance.h"
#include "ScriptManager.h"
#include "ScriptUtitly.h"

namespace App
{


	ScriptInstance::ScriptInstance()
	{

	}

	ScriptInstance::~ScriptInstance()
	{

	}
	void ScriptInstance::Init( const char* cassembly,const char* cnamespace,const char* cclass )
	{
		if(strcmp(cassembly,"RuntimeLibery")!=0)
		{
			printf("can only init from runtime libery");
			return ;
		}
		MonoImage* pImage =	ScriptGeneralManager::GetInstance().GetImage();
		m_pMonoClass = mono_class_from_name(pImage,cnamespace,cclass);

		m_pMonoObj = mono_object_new(mono_domain_get(),m_pMonoClass); // alloc memory;
		m_monoGCHandle = mono_gchandle_new(m_pMonoObj,1); // pin the memory
		
		mono_runtime_object_init(m_pMonoObj);//call .ctor
		SetCppObj<ScriptInstance>( m_pMonoObj,*this );
	}

	void ScriptInstance::OnFrame()
	{
		mono_runtime_invoke(m_pOnFrame,m_pMonoObj,NULL,NULL);
	}

}