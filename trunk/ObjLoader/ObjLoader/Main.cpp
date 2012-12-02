
#include <Windows.h>
#include <stdio.h>

#include "D3D9Device.h"
#include "MeshRenderable.h"
#include "GraphicMgr.h"
#include "ResourceMgr.h"


#include "D3D9Texture.h"
#include "TexLoader.h"

LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice




D3D9Mesh* pMesh;

Renderable* pRenderable;
TexLoader* pTexLoader;
D3D9Texture* pTex;


void InitGeometry()
{
	GraphicMgr::GetInstance().Init();

	pMesh = (D3D9Mesh*)ResourceMgr::GetInstance().GetResByID<MeshResGenerator>(std::string("cup.obj")).get();
	
	pRenderable = new MeshRenderable();
	MeshRenderable* pMeshRenderable =(MeshRenderable*) pRenderable;
	pMeshRenderable->SetRender(GraphicMgr::GetInstance().GetRenderer());
	pMeshRenderable->SetSubMesh( pMesh->GetSubMeshArray()[1] );
	pTexLoader = o_new(TexLoader);
	pTexLoader->LoadFromFile(std::string("Tiny_skin.dds"));
	pTex = o_new(D3D9Texture);
	pTex->SetUp(*pTexLoader);
	o_delete(pTexLoader);
	GraphicMgr::GetInstance().GetRenderableList(COMMONTYPE).push_back(pRenderable);

}

HRESULT InitD3D( HWND hWnd )
{
	// Create the D3D object.
	if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	IDirect3DDevice9** ppDevice = D3D9Device::GetInstance().GetD3DDevice9PP();
	// Create the D3DDevice
	if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, ppDevice ) ) )
	{
		return E_FAIL;
	}
	// Turn off culling
	D3D9Device::GetInstance().GetD3DDevice9()->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	// Turn off D3D lighting
	D3D9Device::GetInstance().GetD3DDevice9()->SetRenderState( D3DRS_LIGHTING, FALSE );

	// Turn on the zbuffer
	D3D9Device::GetInstance().GetD3DDevice9()->SetRenderState( D3DRS_ZENABLE, TRUE );

	//	D3D9Device::GetInstance().GetD3DDevice9()->SetRenderState( D3DRS_FILLMODE,D3DFILL_WIREFRAME );
	return S_OK;
}

VOID Render()
{
	D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	 D3D9Device::GetInstance().GetD3DDevice9()->SetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
	 D3D9Device::GetInstance().GetD3DDevice9()->SetTransform( D3DTS_PROJECTION, &matProj );
	// Clear the backbuffer to a blue color
	 D3D9Device::GetInstance().GetD3DDevice9()->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 100, 125, 150 ), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED(  D3D9Device::GetInstance().GetD3DDevice9()->BeginScene() ) )
	{
		D3D9Device::GetInstance().GetD3DDevice9()->SetTexture(0,pTex->GetD3D9TexturePtr());

		GraphicMgr::GetInstance().OnFrame(0.001f);
		// End the scene
		D3D9Device::GetInstance().GetD3DDevice9()->EndScene();
	}

	// Present the backbuffer contents to the display
	 D3D9Device::GetInstance().GetD3DDevice9()->Present( NULL, NULL, NULL, NULL );
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


	InitD3D( hWnd );

	// Show the window
	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );

	//load
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
			Render();
		}
	}

	UnregisterClass( "D3D Tutorial", wc.hInstance );
	return 0;
}