#include "MeshRenderComponent.h"
#include "..\ScriptFeature\ScriptManager.h"
#include "..\ScriptFeature\ScriptUtitly.h"



using namespace FrameWork;

void ICall_ScriptRuntime_MeshRenderComponent_Regist();

static void ICall_MeshRenderComponent_Bind( MonoObject* pMonoObj )
{
	Ptr<MeshRenderComponent> pMRC = new MeshRenderComponent();
	printf("new cppObject");
	App::MonoCppBind<MeshRenderComponent>(*pMRC,pMonoObj);
	pMRC->AddRef();
}

static void ICall_MeshRenderComponent_SetMeshID( MonoObject* pMonoObj,MonoString* pMonoStr)
{
	std::string ID;
	App::MonoStringToStdString(ID,pMonoStr);
	MeshRenderComponent* pMRC =  App::MonoToCppObj<MeshRenderComponent>(pMonoObj);
	pMRC->SetMeshID(ID);
}

void ICall_ScriptRuntime_MeshRenderComponent_Regist()
{
	mono_add_internal_call("ScriptRuntimeLibrary.MeshRenderComponent::ICall_MeshRenderComponent_Bind",                &ICall_MeshRenderComponent_Bind);
	mono_add_internal_call("ScriptRuntimeLibrary.MeshRenderComponent::ICall_MeshRenderComponent_SetMeshID",           &ICall_MeshRenderComponent_SetMeshID);
}

