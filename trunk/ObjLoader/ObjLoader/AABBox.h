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

aabbox::aabbox()
	:mMax()
	,mMin()
{

}

aabbox::aabbox( aabbox& box )
	:mMax(box.mMax)
	,mMin(box.mMin)
{

}

aabbox::aabbox( point& max,point& min )
	:mMax(max)
	,mMin(min)
{

}
