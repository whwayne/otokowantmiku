#include "Actor.h"
#include "ActorManager.h"
#include "..\ScriptFeature\ScriptManager.h"
#include "..\ScriptFeature\ScriptUtitly.h"



using namespace FrameWork;
using namespace App;

void ICall_ScriptRuntime_ActorMgr_Regist();

static void ICall_ActorMgr_AddActor( MonoObject* pmAct)
{
	Actor* pAct = MonoToCppObj<Actor>(pmAct);
	ActorMgr::GetInstance().AttachActors(pAct);
}

void ICall_ScriptRuntime_ActorMgr_Regist()
{
	mono_add_internal_call("ScriptRuntimeLibrary.ActorMgr::ICall_ActorMgr_AddActor",&ICall_ActorMgr_AddActor);
}
