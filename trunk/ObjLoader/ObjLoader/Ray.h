#pragma once
#include "Point.h"

class ray
{
public:
	ray();
	ray(ray& r);
	ray(point& ori,point& dir);
protected:
	point mOri;
	point mDir;
private:
};

ray::ray()
	:mOri()
	,mDir()
{
	
}

ray::ray( ray& r )
	:mOri(r.mOri)
	,mDir(r.mDir)
{

}

ray::ray( point& ori,point& dir )
	:mOri(ori)
	,mDir(mDir)
{

}
