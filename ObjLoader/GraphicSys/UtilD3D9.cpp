#include "UtilD3D9.h"

HRESULT Util_InitD3D9(HWND hWnd)
{
	LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
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

	return S_OK;
}
