#pragma once
#include "PreCompiledHeaders.h"
#include "MonoApi.h"
#include "MonoType.h"
#include "ScriptClass.h"
#include <map>
#include <string>

namespace App
{
	static const char*  g_csRuntimeLibrary = "..//media//script//bin//ScriptRuntimeLibrary.dll";
	static const char*  g_csUserDef = "..//media//script//bin//UserDefCSharp.dll";

	struct MonoImageMap
	{
		MonoImageMap(const char* _imageName,const MonoImage*  _image )
		{
			p_cImageName = _imageName;
			p_image      = _image;
		}
		const char*		p_cImageName;
		const MonoImage*  p_image;
	};

	enum ScriptImages
	{
		RunTimeLibery ,
		UserDef,
		ImageSize,
	};

	class ScriptGeneralManager
	{
	public:
		static ScriptGeneralManager& GetInstance()
		{
			static ScriptGeneralManager instance;
			return instance;
		}
		virtual ~ScriptGeneralManager();


		void SetupScriptSystem();
		void CallStaticMethod(MonoMethod* method,void** prarm);

		MonoMethod*  GetStaticMethod(const std::string& sig,MonoImage* pImage);

		ScriptClass* GetScriptClass(const std::string& className,MonoImage* pImage);

		ScriptClass* GetScriptClass(const std::string& className);

		MonoImage*   GetRuntimeLibraryImage()
		{
			return m_pRuntimeLibrary;
		}

		MonoImage*   GetUserDefCSharpImage()
		{
			return m_pUserDef;
		}

		ScriptClass& GetEntryBase()
		{
			return m_EntryBase;
		}

	protected:
		ScriptGeneralManager();
		void LoadAssemblies();
		void LoadMonoDLL();
		void LoadEntryBase();
		HMODULE monoDLL;

		MonoImage* m_pRuntimeLibrary ;

		MonoImage* m_pUserDef ;

		std::map<std::string,ScriptClass*> m_mScriptClassCache;

		std::map<std::string,MonoMethod*> m_mStaticFooCache;

		ScriptClass m_EntryBase;
	};
}
