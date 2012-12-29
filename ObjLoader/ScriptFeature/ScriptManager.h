#pragma once
#include "PreCompiledHeaders.h"
#include "MonoApi.h"
#include "MonoType.h"

namespace App
{
	static const char*  g_csRuntimeLibery = "../media/script/bin/runtimeLibery.dll";
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
	//	MonoImageMap m_MonoImages;
	};
}
