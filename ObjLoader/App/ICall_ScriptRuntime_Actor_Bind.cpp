#include "Actor.h"
#include "MeshRenderComponent.h"
#include "..\ScriptFeature\ScriptManager.h"
#include "..\ScriptFeature\ScriptUtitly.h"



using namespace FrameWork;
using namespace App;

void ICall_ScriptRuntime_Actor_Regist();

static void ICall_Actor_Bind( MonoObject* pMonoObj )
{
	Ptr<Actor> pAct = new Actor();
	printf("new cppObject");
	App::MonoCppBind<Actor>(*pAct,pMonoObj);
	pAct->AddRef();
}

static void ICall_Actor_AddComponent( MonoObject* pmAct, MonoObject* pmCom)
{
	Actor* pAct = MonoToCppObj<Actor>(pmAct);
	Component* pCom =  MonoToCppObj<Component>(pmCom);
	pAct->AttachComponent(pCom);
}

void ICall_ScriptRuntime_Actor_Regist()
{
	mono_add_internal_call("ScriptRuntimeLibrary.Actor::ICall_Actor_Bind",         &ICall_Actor_Bind);
	mono_add_internal_call("ScriptRuntimeLibrary.Actor::ICall_Actor_AddComponent",&ICall_Actor_AddComponent);
}

 