#include <Windows.h>
#include <stdio.h>

#include "D3D9Device.h"
#include "MeshRenderable.h"
#include "GraphicMgr.h"
#include "ResourceMgr.h"


#include "D3D9Texture.h"
#include "TexLoader.h"

#include "Thread.h"
#include "CriticalSection.h"
#include "Event.h"

#include "Float2.h"
#include "Float3.h"
#include "Float4.h"
#include "OctTree.h"
#include "Matrix44.h"

#include "..\App\Actor.h"

#include "../ScriptFeature/ScriptManager.h"
#include "../ScriptFeature/ScriptInstance.h"

#include "..\App\GameApp.h"
#include "..\App\MeshRenderComponent.h"
#include "..\App\LogicComponent.h"

LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice

D3D9Mesh* pMesh;

Renderable* pRenderable;
TexLoader* pTexLoader;
D3D9Texture* pTex;

using namespace FrameWork;
void InitGeometry()
{	

	//---------------------------------------ScriptManager------------------------------
	App::ScriptInstance* ScriptInstance = o_new( App::ScriptInstance);
	ScriptInstance->Init(App::ScriptGeneralManager::GetInstance().GetUserDefCSharpImage(),"UserDefCSharp.Move");
	//ScriptInstance->OnFrame();
	//------------------------------------------APP--------------------------------------
	Actor* pAct = new Actor();

	Ptr<MeshRenderComponent> pMC = new MeshRenderComponent();
// 	pMC->SetMeshID("cup.obj");
// 	pAct->AttachComponent(pMC.cast<Component>());

	Ptr<LogicComponent>      pLC = new LogicComponent();
	pLC->AddScriptInstance(Ptr<App::ScriptInstance>(ScriptInstance));
	pAct->AttachComponent(pLC.cast<Component>());

	ActorMgr::GetInstance().AttachActors( Ptr<Actor>(pAct) );

}

void OnFrame()
{
	GameApp::GetInstance().OnBeginFrame(0.01f);
	GameApp::GetInstance().OnFrame(0.01f);
}



VOID Render()
{
	GameApp::GetInstance().BackGroundTick(0.01f);
}

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:

		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}



int main()
{
	
	WNDCLASSEX wc =
	{
		sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
		"Obj", NULL
	};
	RegisterClassEx( &wc );

	HWND hWnd = CreateWindow( "Obj", "ObjLoader",
		WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
		NULL, NULL, wc.hInstance, NULL );

	GameApp::GetInstance().SetUp(hWnd);

	// Show the window
	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	InitGeometry();
	// Enter the message loop
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	while( msg.message != WM_QUIT )
	{
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			OnFrame();
			Render();
		}
	}
	UnregisterClass( "D3D Tutorial", wc.hInstance );
	//Memory::DestoryHeaps();
	return 0;
}