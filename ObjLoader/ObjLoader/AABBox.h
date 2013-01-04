#pragma once
#include "Point.h"
#include <vector>

class matrix44; 

class aabbox
{
public:
	aabbox();
	aabbox(const aabbox& box);
	aabbox(const point& max,const point& min);
	/// assignment operator
	void operator=(const aabbox& rhs);

	void   SetMax(const point& max);
	void   SetMin(const point& min);
	point& GetMax() ;
	point& GetMin() ;

	InterSectResult InterSect(const aabbox& box);

	InterSectResult InterSect(const matrix44& viewProj);
	std::vector<point> FormPoint();


	aabbox Transform(const matrix44& mtra);
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

inline aabbox::aabbox(const aabbox& box )
	:mMax(box.mMax)
	,mMin(box.mMin)
{

}

inline aabbox::aabbox(const point& max,const point& min )
	:mMax(max)
	,mMin(min)
{

}



inline point& aabbox::GetMax() 
{
	return mMax;
}

inline point& aabbox::GetMin() 
{
	return mMin;
}

inline void aabbox::SetMax(const point& max )
{	
	mMax = max;
}

inline void aabbox::SetMin(const point& min )
{
	mMin = min;
}

inline void aabbox::operator=( const aabbox& rhs )
{
	mMax = rhs.mMax;
	mMin = rhs.mMin;
}
