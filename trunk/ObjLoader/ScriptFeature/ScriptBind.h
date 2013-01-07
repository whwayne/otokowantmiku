#pragma once
#include "PreCompiledHeaders.h"
#include "MonoApi.h"
#include "MonoType.h"
#include "ScriptUtitly.h"



namespace App
{


#define __Scriptbind \
public: \
void SetMonoObj(MonoObject* pObj){m_ScriptBind.SetMonoObj(pObj);}\
MonoObject* GetMonoObj(){return m_ScriptBind.GetMonoObj();}\
private: \
App::ScriptBind m_ScriptBind;\



	class ScriptBind
	{
	public:
		ScriptBind()
			:m_pMonoObj(0)
			,m_iGcHandle(0)
		{

		}
		~ScriptBind()
		{

		}
		void SetMonoObj(MonoObject* pObj)
		{
			if(pObj!=NULL)
			{
				m_pMonoObj = pObj;
				m_iGcHandle = mono_gchandle_new(pObj,1);
			}
			else
			{
				if(m_pMonoObj!=NULL)
				{	
					m_pMonoObj = pObj;
					mono_gchandle_free(m_iGcHandle);
					m_iGcHandle = 0;
				}
			}
		}
		
		MonoObject* GetMonoObj()
		{
			return m_pMonoObj;
		}
	protected:
	private:
		MonoObject* m_pMonoObj;
		int         m_iGcHandle;
	};
}