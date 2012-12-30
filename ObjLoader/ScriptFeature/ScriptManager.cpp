#include "PreCompiledHeaders.h"
#include "ScriptManager.h"
#include "MonoFunRegist.h"
#include "ScriptClass.h"
#include "../MikuCore/UtilStr.h"
#include "../MikuCore/Memory.h"

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
		MonoAssembly* pAssemly = mono_domain_assembly_open(pDomain,g_csRuntimeLibrary); 
		m_pRuntimeLibery = mono_assembly_get_image(pAssemly);
	}

	ScriptGeneralManager::ScriptGeneralManager()
		:monoDLL(NULL)
		,m_pRuntimeLibery(NULL)
	{

	}

	ScriptGeneralManager::~ScriptGeneralManager()
	{
		std::map<std::string,ScriptClass*>::iterator iter;
		for( iter = m_mScriptClassCache.begin();iter!=m_mScriptClassCache.end();iter++ )
		{
			o_delete(iter->second);
		}

	}

	void ScriptGeneralManager::LoadMonoDLL()
	{
		monoDLL = LoadLibrary("../external_dlls_debug/mono-2.0.dll");

#undef MONO_API
#define MONO_API(ret,fun,params) fun=(fp##fun##Type) GetProcAddress(monoDLL,#fun);
		ALL_MONO_API

	
	}


	MonoMethod* ScriptGeneralManager::GetStaticMethod(const std::string& sig,MonoImage* pImage)
	{
		std::map<std::string,MonoMethod*>::iterator iter = m_mStaticFooCache.find(sig);
		if (iter!=m_mStaticFooCache.end())
		{
			return iter->second;
		}
		else
		{
			MonoMethodDesc* pSig = mono_method_desc_new(sig.c_str(),false);
			MonoMethod* pMethod  = mono_method_desc_search_in_image( pSig, pImage);
			mono_method_desc_free(pSig);
			m_mStaticFooCache.insert(std::pair<std::string,MonoMethod*>(sig,pMethod));
			return pMethod;
		}
	}

	void ScriptGeneralManager::CallStaticMethod(MonoMethod* method,void** prarm)
	{
		mono_runtime_invoke(method,NULL,prarm,NULL);
	}

	ScriptClass* ScriptGeneralManager::GetScriptClass( const std::string& className,MonoImage* pImage )
	{
		std::map<std::string,ScriptClass*>::iterator iter = m_mScriptClassCache.find(className);

		std::vector<std::string> name = Util_StrToken(className,std::string("."));
		if (iter!=m_mScriptClassCache.end())
		{
			return iter->second;
		}
		else
		{
			ScriptClass* pSClass = o_new(App::ScriptClass);
			pSClass->Init( pImage,  name[0] ,name[2]);

			m_mScriptClassCache.insert(std::pair<std::string,ScriptClass*>(className,pSClass));
			return pSClass;
		}
	}
}

