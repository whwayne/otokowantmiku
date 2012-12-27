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

inline ray::ray()
	:mOri()
	,mDir()
{
	
}

inline ray::ray( ray& r )
	:mOri(r.mOri)
	,mDir(r.mDir)
{

}

inline ray::ray( point& ori,point& dir )
	:mOri(ori)
	,mDir(mDir)
{

}
