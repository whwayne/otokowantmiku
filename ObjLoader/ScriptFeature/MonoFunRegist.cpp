#include "MonoFunRegist.h"
#include "PreCompiledHeaders.h"

void OutPutToScreen()
{
	printf("Script Entry Success");
}

void ICall_ScriptRuntime_Actor_Regist();
void ICall_ScriptRuntime_MeshRenderComponent_Regist();
void ICall_ScriptRuntime_ActorMgr_Regist();

void RegistInternalCalls()
{
	mono_add_internal_call("ScriptRuntimeLibrary.Util::OutPutToScreen()",&OutPutToScreen);
	ICall_ScriptRuntime_Actor_Regist();
	ICall_ScriptRuntime_MeshRenderComponent_Regist();
	ICall_ScriptRuntime_ActorMgr_Regist();
}