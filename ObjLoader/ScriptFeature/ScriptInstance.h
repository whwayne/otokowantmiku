#pragma once
#include "PreCompiledHeaders.h"
#include "MonoApi.h"
#include "MonoType.h"
#include "ScriptBind.h"
#include "..\MikuCore\Res.h"

namespace App
{
	
	class ScriptClass;
	class ScriptInstance:public Res
	{
		__Scriptbind
	public:
		enum EntryMethod
		{
			MethodOnFrame = 0,
			MethodCount,
		};
	public:
		ScriptInstance();
		~ScriptInstance();
		void OnFrame();
		void Init(MonoImage* pImage  ,   const char* className);

	private:
		void GetMethods(MonoClass* pClass);
	private:

		MonoMethod*  m_pEntryMethods[ScriptInstance::MethodCount];
		ScriptClass* m_pScriptClass;
	};

	static const char* scEntryMethodNames[ScriptInstance::MethodCount] = 
	{
		"*:OnFrame()"
	};
}