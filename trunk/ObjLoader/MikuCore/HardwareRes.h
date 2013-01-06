#pragma once
#include "..\MikuCore\Res.h"
#include "..\MikuCore\Loader.h"

class HardwareRes:public Res
{
public:
	HardwareRes(){}
	virtual ~HardwareRes(){}
	virtual bool SetUp(Loader& loader){return false;}
	virtual void Copy(HardwareRes& rhs){}
protected:
private:
};