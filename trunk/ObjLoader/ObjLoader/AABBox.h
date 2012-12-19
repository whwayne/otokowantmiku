#pragma once
#include "Point.h"

class aabbox
{
public:
	aabbox();
	aabbox(aabbox& box);
	aabbox(point& max,point& min);

protected:
	point mMax;
	point mMin;
private:
};

inline aabbox::aabbox()
	:mMax()
	,mMin()
{

}

inline aabbox::aabbox( aabbox& box )
	:mMax(box.mMax)
	,mMin(box.mMin)
{

}

inline aabbox::aabbox( point& max,point& min )
	:mMax(max)
	,mMin(min)
{

}
