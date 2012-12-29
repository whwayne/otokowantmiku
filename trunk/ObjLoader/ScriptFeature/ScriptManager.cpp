#include "PreCompiledHeaders.h"
#include "ScriptManager.h"
#include "MonoFunRegist.h"



#undef MONO_API
#define MONO_API(ret,fun,params) typedef ret (*fp##fun##Type) params;

ALL_MONO_API

#undef MONO_API
#define MONO_API(ret,fun,params) fp##fun##Type fun=NULL;

ALL_MONO_API



namespace App
{
	

	void ScriptGeneralManager::SetupScriptSystem()
	{
		LoadMonoDLL();
		mono_jit_init_version("MainDomain","v2.0.50727");
		
		LoadAssemblies();
		RegistInternalCalls();
	}

	void ScriptGeneralManager::LoadAssemblies()
	{
	    MonoDomain* pDomain =  mono_domain_get();
		MonoAssembly* pAssemly = mono_domain_assembly_open(pDomain,g_csRuntimeLibery); 
		m_pRuntimeLibery = mono_assembly_get_image(pAssemly);
	}

	ScriptGeneralManager::ScriptGeneralManager()
		:monoDLL(NULL)
		,m_pRuntimeLibery(NULL)
	{

	}

	ScriptGeneralManager::~ScriptGeneralManager()
	{

	}

	void ScriptGeneralManager::LoadMonoDLL()
	{
		monoDLL = LoadLibrary("../external_dlls_debug/mono-2.0.dll");

#undef MONO_API
#define MONO_API(ret,fun,params) fun=(fp##fun##Type) GetProcAddress(monoDLL,#fun);
		ALL_MONO_API

	
	}

	void ScriptGeneralManager::CallStaticMethod(MonoMethod* method,void** prarm)
	{
		mono_runtime_invoke(method,NULL,prarm,NULL);
	}

}

