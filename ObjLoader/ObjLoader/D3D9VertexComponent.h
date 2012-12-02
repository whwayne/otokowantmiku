#pragma once
#include "D3D9Device.h"
#include "Res.h"

class D3D9VertexComponent:public Res
{
public:
	enum Type
	{
		COM_UNUSED = -1,
		COM_POSITION = 0,
		COM_NORMAL,
		COM_UV,
	};
public:
	D3D9VertexComponent();
	D3D9VertexComponent(Type type);
	virtual ~D3D9VertexComponent();
	
	void SetType(Type type)
	{
		m_type =  type;
	}

	Type GetType()
	{
		return m_type;
	}
protected:
	Type m_type;
private:
};