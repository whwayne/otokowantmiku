#pragma once
#include "D3D9Device.h"
#include "D3D9Res.h"

class D3D9VertexLayout:public D3D9Res
{
public:

	D3D9VertexLayout();
	virtual ~D3D9VertexLayout();

	



protected:

	IDirect3DVertexDeclaration9* m_pVertexDeclaration;
private:
};