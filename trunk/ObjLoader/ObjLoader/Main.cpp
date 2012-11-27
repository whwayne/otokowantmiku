
#include <Windows.h>
#include <stdio.h>
#include "ObjLoader.h"
#include "D3D9Device.h"


LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold Vertices
LPDIRECT3DINDEXBUFFER9  g_pIB = NULL;

ObjLoader* obj;

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
	FLOAT x, y, z; // The transformed position for the vertex
	FLOAT nx,ny,nz;
	FLOAT u,v;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX0|D3DFVF_NORMAL)

void InitGeometry()
{
	obj = new ObjLoader();
	obj->LoadObjFromFile(std::string("cup.obj"));

	std::vector<ObjSubMeshContent>& content = obj->GetContent();

	int vertexCount = content[0].mVertexBuffer.size()/8;

	if( FAILED( D3D9Device::GetInstance().GetD3DDevice9()->CreateVertexBuffer(vertexCount*sizeof( CUSTOMVERTEX ),
		0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &g_pVB, NULL ) ) )
	{
		return ;
	}
	CUSTOMVERTEX* pVertices ;
	g_pVB->Lock(0, 0, ( void** )&pVertices, 0 );
	memcpy(pVertices,&content[0].mVertexBuffer[0],vertexCount*sizeof( CUSTOMVERTEX ));
	g_pVB->Unlock();


	if( FAILED( D3D9Device::GetInstance().GetD3DDevice9()->CreateIndexBuffer(content[0].mVertexIndexBuffer.size()*sizeof( int ),0,D3DFMT_INDEX32,D3DPOOL_DEFAULT,&g_pIB,NULL ) ) )
	{
		return ;
	}

	int* pIndex ;
	g_pIB->Lock(0, 0,( void** )&pIndex, 0 );
	memcpy(pIndex,&content[0].mVertexIndexBuffer[0],content[0].mVertexIndexBuffer.size()*sizeof( int ));
	g_pIB->Unlock();

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
	D3D9Device::GetInstance().GetD3DDevice9()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

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

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
	 D3D9Device::GetInstance().GetD3DDevice9()->SetTransform( D3DTS_PROJECTION, &matProj );
	// Clear the backbuffer to a blue color
	 D3D9Device::GetInstance().GetD3DDevice9()->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 100, 125, 150 ), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED(  D3D9Device::GetInstance().GetD3DDevice9()->BeginScene() ) )
	{
		// Draw the triangles in the vertex buffer. This is broken into a few
		// steps. We are passing the Vertices down a "stream", so first we need
		// to specify the source of that stream, which is our vertex buffer. Then
		// we need to let D3D know what vertex shader to use. Full, custom vertex
		// shaders are an advanced topic, but in most cases the vertex shader is
		// just the FVF, so that D3D knows what type of Vertices we are dealing
		// with. Finally, we call DrawPrimitive() which does the actual rendering
		// of our geometry (in this case, just one triangle).
		 D3D9Device::GetInstance().GetD3DDevice9()->SetIndices(g_pIB);
 		 D3D9Device::GetInstance().GetD3DDevice9()->SetStreamSource( 0, g_pVB, 0, sizeof( CUSTOMVERTEX ) );
 		 D3D9Device::GetInstance().GetD3DDevice9()->SetFVF( D3DFVF_CUSTOMVERTEX );
 		// D3D9Device::GetInstance().GetD3DDevice9()->DrawPrimitive( D3DPT_TRIANGLELIST, 0, obj->GetContent()[0].mVertexIndexBuffer.size()/3 );


		  D3D9Device::GetInstance().GetD3DDevice9()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,obj->GetContent()[0].mVertexBuffer.size()/8,0,obj->GetContent()[0].mVertexIndexBuffer.size()/3);

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