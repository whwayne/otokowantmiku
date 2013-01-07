#ifndef Script_Utitly_H
#define Script_Utitly_H

#include "MonoApi.h"
#include "MonoType.h"
#include "ScriptManager.h"
#include "..\MikuCore\RttiMacros.h"
#include <string>
#include <assert.h>

namespace App
{
	inline void MonoStringToStdString(std::string& str,MonoString* pMonoString)
	{
		str = mono_string_to_utf8(pMonoString);
	}

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
		int* pHeadData = (int*)GetDataOnHead(pMonoObj);
		*pHeadData =(int) &cppObj;
	}

	template <typename T>
	void MonoCppBind(T& cppObj,MonoObject* pMonoObj)
	{
		SetMonoObj(cppObj,pMonoObj);
		SetCppObj(pMonoObj,cppObj);
	}
	
	template <typename T>
	T* MonoToCppObj(MonoObject* pMonoObj)
	{
		int* add = (int*)GetDataOnHead(pMonoObj);

		void* pAddress = reinterpret_cast<void*>(*add); 
		return (T*)pAddress;
	}

	inline	MonoObject* GetDummyObj()
	{
		ScriptClass* pClass = NULL;
		pClass = ScriptGeneralManager::GetInstance().GetScriptClass("ScriptRuntime.__DummyClass");
		MonoObject* pObj =	mono_object_new( mono_domain_get(),pClass->GetMonoClass() );
		mono_runtime_object_init(pObj);

		return pObj;
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
			std::string className("ScriptRuntime.");
			className+=cppObj::RTTI.GetTypeName();

			pClass = ScriptGeneralManager::GetInstance().GetScriptClass(className);
			assert(pClass);
			MonoObject* pObj =	mono_object_new( mono_domain_get(),pClass->GetMonoClass() );
		
			MonoObject* pDummy = GetDummyObj();

			MonoMethodDesc* pSig = mono_method_desc_new(".ctor(__DummyClass)",false);
 			MonoMethod* pMethod  = mono_method_desc_search_in_class( pSig, pClass);
 			mono_method_desc_free(pSig);

			void*[1] param;
			param[0] = pDummy;
			mono_runtime_invoke(pMethod,pObj,param,0);

			assert(pObj);
			MonoCppBind<T>(cppObj,pObj);
			return cppObj.GetMonoObj();
		}
	}
}
#endif