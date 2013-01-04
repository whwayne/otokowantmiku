#pragma once
#include "Float4.h"

typedef float4 point;
// class point
// {
// public:
// 	point();
// 	point(point& p);
// 	point(float4& pos);
// 	point(float x,float y,float z);
// 	/// assignment operator
// 	void operator=(const point& rhs);
// 	/// subtract 2 vectors
// 	point operator-(const point& rhs) const;
// 	float4& GetPos()
// 	{
// 		return mPos;
// 	}
// protected:
// 	float4 mPos;
// private:
// };
// 
// point::point()
// 	:mPos(float4(0.0f,0.0f,0.0f,1.0f))
// {
// 
// }
// 
// point::point( point& p )
// 	:mPos(p.mPos)
// {
// 
// }
// 
// point::point( float4& pos )
// 	:mPos(pos)
// {
// 
// }
// 
// point::point( float x,float y,float z )
// 	:mPos(x,y,z,1.0f)
// {
// 
// }
// 
// void point::operator=( const point& rhs )
// {
// 	mPos = rhs.mPos;
// }
// 
// point point::operator-( const point& rhs ) const
// {
// 	return point(mPos-rhs.mPos);
// }
