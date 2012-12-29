#pragma once
#include "PreCompiledHeaders.h"
#include "MonoApi.h"
#include "MonoType.h"

namespace App
{
	class ScriptInstance
	{
	public:
		ScriptInstance();
		~ScriptInstance();
		void OnFrame();
		void Init(const char* cassembly  ,   const char* cnamespace   ,const char* cclass);

	private:
		int          m_monoGCHandle;
		MonoMethod*  m_pOnFrame;
		MonoObject*  m_pMonoObj;
		MonoClass*   m_pMonoClass;
	};
}