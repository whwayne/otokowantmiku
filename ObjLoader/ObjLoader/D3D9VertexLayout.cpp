#include "D3D9VertexLayout.h"

D3D9VertexLayout::D3D9VertexLayout()
	:m_pD3D9VertexDeclaration(NULL)
{

}

D3D9VertexLayout::~D3D9VertexLayout()
{
	if (m_pD3D9VertexDeclaration)
	{
		m_pD3D9VertexDeclaration->Release();
	}
}

void D3D9VertexLayout::SetUp()
{
	if (m_pD3D9VertexDeclaration)
	{
		m_pD3D9VertexDeclaration->Release();
		m_pD3D9VertexDeclaration = NULL;
	}
	
	int offSet = 0;
	std::vector<D3DVERTEXELEMENT9> elementAarray;
	for (int i = 0; i < m_Components.size(); ++i)  
	{ 
		D3DVERTEXELEMENT9 ele;
		switch(m_Components[i].GetType())
		{
				
			case D3D9VertexComponent::COM_NORMAL:
				
				ele.Method = 0;
				ele.Offset = offSet;
				ele.Type = D3DDECLTYPE_FLOAT3;
				ele.Stream = D3DDECLMETHOD_DEFAULT;
				ele.Usage = D3DDECLUSAGE_NORMAL;
				ele.UsageIndex = 0;
				elementAarray.push_back( ele);
				offSet+=12;
				break;
			case D3D9VertexComponent::COM_POSITION:
			
				ele.Method = 0;
				ele.Offset = offSet;
				ele.Type = D3DDECLTYPE_FLOAT3;
				ele.Stream = D3DDECLMETHOD_DEFAULT;
				ele.Usage = D3DDECLUSAGE_POSITION;
				ele.UsageIndex = 0;
				elementAarray.push_back( ele);
				offSet+=12;
				break;
			case D3D9VertexComponent::COM_UV:
				ele.Method = 0;
				ele.Offset = offSet;
				ele.Type = D3DDECLTYPE_FLOAT2;
				ele.Stream = D3DDECLMETHOD_DEFAULT;
				ele.Usage = D3DDECLUSAGE_TEXCOORD;
				ele.UsageIndex = 0;
				elementAarray.push_back( ele);
				offSet+=8;
				break;
			default:
				break;
		};
	}

	D3DVERTEXELEMENT9 eleEnd = D3DDECL_END();  
	elementAarray.push_back( eleEnd);
	HRESULT hr = D3D9Device::GetInstance().GetD3DDevice9()->CreateVertexDeclaration((const D3DVERTEXELEMENT9 *) &elementAarray[0], &m_pD3D9VertexDeclaration); 
	if (hr!=S_OK)
	{

	}
}
