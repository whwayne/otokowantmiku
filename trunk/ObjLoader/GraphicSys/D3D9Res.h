#pragma once
#include "..\MikuCore\Res.h"
#include "..\MikuCore\Loader.h"

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