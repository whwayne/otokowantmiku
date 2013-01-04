#pragma once
#include "Ray.h"
#include <assert.h>

class Plane
{
public:
	Plane();
	Plane(const Plane& pla);
	//explicit Plane(const Plane& pla);
	Plane(float a,float b,float c,float d);
	Plane(ray& r1,ray& r2);
	Plane(point& ori,point& dir1,point& dir2);

	/// assignment operator
	 void  operator=(const Plane& rhs);

	virtual ~Plane();

	float A;
	float B;
	float C;
	float D;
protected:

private:
};


inline Plane::Plane()
:A(0.f)
,B(0.f)
,C(0.f)
,D(0.f)
{

}

inline Plane::Plane(const Plane& pla )
:A(pla.A)
,B(pla.B)
,C(pla.C)
,D(pla.D)
{

}


inline Plane::Plane( float a,float b,float c,float d )
:A(a)
,B(b)
,C(c)
,D(d)
{

}

inline Plane::Plane( ray& r1,ray& r2 )
:A(0.f)
,B(0.f)
,C(0.f)
,D(0.f)
{
	
}

inline Plane::Plane( point& ori,point& dir1,point& dir2 )
:A(0.f)
,B(0.f)
,C(0.f)
,D(0.f)
{
	float4 _normal = float4::cross3(dir1,dir2);
	A = _normal.X();
	B = _normal.Y();
	C = _normal.Z();
	D = -(A*ori.X()+B*ori.Y()+C*ori.Z());
}


inline Plane::~Plane()
{

}


inline void Plane::operator=( const Plane& rhs )
{
	A = rhs.A;
	B = rhs.B;
	C = rhs.C;
	D = rhs.D;
}
