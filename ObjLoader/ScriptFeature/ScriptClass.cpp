#include "ScriptClass.h"
#include <assert.h>

namespace App
{
	bool ScriptClass::Init( MonoImage* pImage,const std::string& namespaceName ,const std::string& className)
	{
		m_pClass = mono_class_from_name(pImage,namespaceName.c_str(),className.c_str());
		if (m_pClass)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	MonoMethod*  ScriptClass::GetMethod( const std::string& sig)
	{
		std::map<std::string,MonoMethod*>::iterator iter = m_mMethodCache.find(sig);
		if ( iter!= m_mMethodCache.end() )
		{
			return iter->second;
		}
		else
		{
			MonoMethodDesc* pSig = mono_method_desc_new(sig.c_str(),false);
			MonoMethod* pMethod  = mono_method_desc_search_in_class( pSig, m_pClass);
			mono_method_desc_free(pSig);
			m_mMethodCache.insert(std::pair<std::string,MonoMethod*>(sig,pMethod));
			return pMethod;
		}
	}

	ScriptClass::ScriptClass()
		:m_pClass(0)
		,m_mMethodCache()
	{

	}

	ScriptClass::~ScriptClass()
	{

	}

}