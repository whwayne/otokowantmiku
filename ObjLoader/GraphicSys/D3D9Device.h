#pragma once
#include <d3d9.h>

class D3D9Device
{
public:
	static D3D9Device& GetInstance()
	{
		static D3D9Device instance;
		return instance;
	}
	virtual ~D3D9Device();
	
public:

	IDirect3DDevice9* GetD3DDevice9()
	{
		return m_pDevice9;
	}
	IDirect3DDevice9** GetD3DDevice9PP()
	{
		return &m_pDevice9;
	}
protected:
	IDirect3DDevice9* m_pDevice9;
	D3D9Device();
private:
};