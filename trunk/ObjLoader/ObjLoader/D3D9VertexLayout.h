#pragma once
#include "D3D9Device.h"
#include "Res.h"
#include "D3D9VertexComponent.h"
#include <vector>

class D3D9VertexLayout:public Res
{
public:

	D3D9VertexLayout();
	virtual ~D3D9VertexLayout();

	virtual void AddComponent(D3D9VertexComponent& com)
	{
		m_Components.push_back(com);
	}
	
	IDirect3DVertexDeclaration9* GetD3D9VertexDeclarationPtr()
	{
		return m_pD3D9VertexDeclaration;
	}
	void SetUp();
protected:
	
protected:

	std::vector<D3D9VertexComponent> m_Components;
	IDirect3DVertexDeclaration9* m_pD3D9VertexDeclaration;

private:
};