#pragma once
#include "Res.h"
#include "Loader.h"

class D3D9Res:public Res
{
public:
	D3D9Res(){}
	virtual ~D3D9Res(){}
	virtual bool SetUp(Loader& loader){return false;}
	virtual void Copy(D3D9Res& rhs){}
protected:
private:
};