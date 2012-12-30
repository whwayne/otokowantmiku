#pragma once
#include "PreCompiledHeaders.h"
#include "MonoApi.h"
#include "MonoType.h"
#include <map>
#include <string>



namespace App
{
	class ScriptClass
	{
	public:
		ScriptClass();
		virtual ~ScriptClass();
		
		void Init( MonoImage* pImage,const std::string& namespaceName ,const std::string& className);

		MonoMethod* GetMethod( const std::string& sig);

		MonoClass* GetMonoClass()
		{
			return m_pClass;
		}
	protected:
		MonoClass* m_pClass;
		std::map<std::string,MonoMethod*>  m_mMethodCache;
	};
}