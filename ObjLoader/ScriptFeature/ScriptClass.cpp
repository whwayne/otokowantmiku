#include "ScriptClass.h"

namespace App
{
	void ScriptClass::Init( MonoImage* pImage,const std::string& namespaceName ,const std::string& className)
	{
		m_pClass = mono_class_from_name(pImage,namespaceName.c_str(),className.c_str());
	}

	MonoMethod*  ScriptClass::GetMethod( const std::string& sig)
	{
		MonoMethodDesc* pSig = mono_method_desc_new(sig.c_str(),false);
		MonoMethod* pMethod  = mono_method_desc_search_in_class( pSig, m_pClass);
		mono_method_desc_free(pSig);
		return pMethod;
	}
}