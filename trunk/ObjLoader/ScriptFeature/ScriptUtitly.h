#ifndef Script_Utitly_H
#define Script_Utitly_H

#include "MonoApi.h"
#include "MonoType.h"

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
	MonoObject* CppObjToScriptObj(T& cppObj)
	{
		return cppObj.GetMonoObj();
	}
}
#endif