#pragma once
#include "..\MikuCore\HardwareRes.h"
#include "..\MikuCore\Loader.h"

class D3D9Res:public HardwareRes
{
public:
	D3D9Res(){}
	virtual ~D3D9Res(){}
	virtual bool SetUp(Loader& loader){return false;}
	virtual void Copy(HardwareRes& rhs){}
protected:
private:
};