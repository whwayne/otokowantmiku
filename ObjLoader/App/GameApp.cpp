#include "GameApp.h"
#include "..\MikuCore\Memory.h"
#include "..\GraphicSys\UtilD3D9.h"
#include "..\GraphicSys\GraphicMgr.h"

#include "..\Util\Matrix44.h"

namespace FrameWork
{
	GameApp::GameApp()
	{
		
	}

	GameApp::~GameApp()
	{

	}

	void GameApp::SetUp( HWND hWnd )
	{
		//base
		Memory::SetUpHeaps();
		//graphic
		Util_InitD3D9(hWnd);
		GraphicMgr::GetInstance().Init();
		//res
		LoaderThread::GetInstance().Start();
		//script
		App::ScriptGeneralManager::GetInstance().SetupScriptSystem();
	}

	void GameApp::Exit()
	{
		Memory::DestoryHeaps();
	}

	void GameApp::OnBeginFrame( float deltaTime )
	{
		ResourceMgr::GetInstance().OnBeginFrame();
	}

	void GameApp::OnFrame( float deltaTime )
	{
		ActorMgr::GetInstance().OnFrame(deltaTime);
	}

	void GameApp::BackGroundTick( float deltaTime )
	{
		OnRender(deltaTime);
	}

	void GameApp::OnRender( float deltaTime )
	{
		D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
		D3DXVECTOR3 vLookatPt( 0.0f,0.0f, 0.0f );
		D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
		D3DXMATRIXA16 matView;
		D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
		D3D9Device::GetInstance().GetD3DDevice9()->SetTransform( D3DTS_VIEW, &matView );

		matrix44* m44View = (matrix44*)&matView;
		matrix44 m44Proj = matrix44::ProjectionLH(1.f,100.f,1.57f/2,1.57f/2);
		GraphicMgr::GetInstance().SetViewProj((*m44View)*m44Proj);

		D3D9Device::GetInstance().GetD3DDevice9()->SetTransform( D3DTS_PROJECTION, (const D3DMATRIX *)&m44Proj );
		// Clear the backbuffer to a blue color
		D3D9Device::GetInstance().GetD3DDevice9()->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 100, 125, 150 ), 1.0f, 0 );

		// Begin the scene
		if( SUCCEEDED(  D3D9Device::GetInstance().GetD3DDevice9()->BeginScene() ) )
		{
			GraphicMgr::GetInstance().OnFrame(deltaTime);
			// End the scene
			D3D9Device::GetInstance().GetD3DDevice9()->EndScene();
		}

		// Present the backbuffer contents to the display
		D3D9Device::GetInstance().GetD3DDevice9()->Present( NULL, NULL, NULL, NULL );

	}

}
