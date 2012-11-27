#pragma once
#include "Res.h"

class D3D9Res:public Res
{
public:
	D3D9Res(){}
	virtual ~D3D9Res(){}
	virtual void Copy(D3D9Res& rhs){}
protected:
private:
};