#ifndef Script_Utitly_H
#define Script_Utitly_H

#include "MonoApi.h"
#include "MonoType.h"
#include "ScriptManager.h"
#include "..\MikuCore\RttiMacros.h"
#include <assert.h>

namespace App
{
	inline void*  GetDataOnHead(MonoObject* pObj)
	{
		return (void*) ((int)pObj + 8);
	}

	template <typename T>
	void SetMonoObj(T& cppObj,MonoObject* pMonoObj)
	{
		cppObj.SetMonoObj(pMonoObj);
	}

	template <typename T>
	void SetCppObj( MonoObject* pMonoObj, T& cppObj )
	{
		void* pHeadData = GetDataOnHead(pMonoObj);
		pHeadData = &cppObj;
	}

	template <typename T>
	void MonoCppBind(T& cppObj,MonoObject* pMonoObj)
	{
		SetMonoObj(cppObj,pMonoObj);
		SetCppObj(pMonoObj,cppObj);
	}

	template <typename T>
	MonoObject* CppObjToScriptObj(T& cppObj,const char* scriptClassName)
	{
		MonoObject* pRet = NULL;
		pRet = cppObj.GetMonoObj();
		if (pRet)
		{
			return pRet;
		}
		else
		{
			ScriptClass* pClass = NULL;
			pClass = ScriptGeneralManager::GetInstance().GetScriptClass(scriptClassName);
			assert(pClass);
		    MonoObject* pObj =	mono_object_new( mono_domain_get(),pClass->GetMonoClass() );
			assert(pObj);
			MonoCppBind<T>(cppObj,pObj);
			return cppObj.GetMonoObj();
		}
	}

	template <typename T>
	MonoObject* CppObjToScriptObj(T& cppObj)
	{
		MonoObject* pRet = NULL;
		pRet = cppObj.GetMonoObj();
		if (pRet)
		{
			return pRet;
		}
		else
		{
			ScriptClass* pClass = NULL;
			pClass = ScriptGeneralManager::GetInstance().GetScriptClass(cppObj::RTTI.GetTypeName());
			assert(pClass);
			MonoObject* pObj =	mono_object_new( mono_domain_get(),pClass->GetMonoClass() );
			assert(pObj);
			MonoCppBind<T>(cppObj,pObj);
			return cppObj.GetMonoObj();
		}
	}
}
#endif