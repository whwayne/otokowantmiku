#pragma once
#include "PreCompiledHeaders.h"
#include "MonoApi.h"
#include "MonoType.h"
#include <map>
#include <string>

namespace App
{
	static const char*  g_csRuntimeLibrary = "..//media//script//bin//ScriptRuntimeLibrary.dll";
	static const char*  g_csUserDef = "../media/script/bin/userDef.dll";

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

	class ScriptClass;
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

		MonoMethod* GetStaticMethod(const std::string& sig,MonoImage* pImage);

		ScriptClass* GetScriptClass(const std::string& className,MonoImage* pImage);

		MonoImage* GetImage()
		{
			return m_pRuntimeLibery;
		}
	protected:
	private:
		ScriptGeneralManager();
		void LoadAssemblies();
		void LoadMonoDLL();
		HMODULE monoDLL;

		MonoImage* m_pRuntimeLibery ;


		std::map<std::string,ScriptClass*> m_mScriptClassCache;

		std::map<std::string,MonoMethod*> m_mStaticFooCache;
	};
}
