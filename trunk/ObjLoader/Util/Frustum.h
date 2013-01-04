#pragma once
#include "Point.h"
#include "Plane.h"
#include <vector>
#include "AABBox.h"

class Frustum
{
public:
	Frustum();
	Frustum(Frustum& ftm);
	Frustum(point FLUp,point FLBp,point FRUp,point FRBp,point NLUp,point NLBp,point NRUp,point NRBp );

	virtual ~Frustum();

	InterSectResult InterSect(aabbox& box);

	bool InterSect(point& p);

	unsigned int InterSectClip(point& p);

	std::vector<Plane>	FormPlane();

	
	point m_FLUp;
	point m_FLBp;
	point m_FRUp;
	point m_FRBp;

	point m_NLUp;
	point m_NLBp;
	point m_NRUp;
	point m_NRBp;
protected:	
	
	
private:
};

inline Frustum::Frustum()
:m_FLUp()
,m_FLBp()
,m_FRUp()
,m_FRBp()
,m_NLUp()
,m_NLBp()
,m_NRUp()
,m_NRBp()
{

}

inline Frustum::Frustum( Frustum& ftm )
:m_FLUp(ftm.m_FLUp)
,m_FLBp(ftm.m_FLBp)
,m_FRUp(ftm.m_FRUp)
,m_FRBp(ftm.m_FRBp)
,m_NLUp(ftm.m_NLUp)
,m_NLBp(ftm.m_NLBp)
,m_NRUp(ftm.m_NRUp)
,m_NRBp(ftm.m_NRBp)
{

}

inline Frustum::Frustum( point FLUp,point FLBp,point FRUp,point FRBp,point NLUp,point NLBp,point NRUp,point NRBp )
 :m_FLUp(FLUp)
 ,m_FLBp(FLBp)
 ,m_FRUp(FRUp)
 ,m_FRBp(FRBp)
 ,m_NLUp(NLUp)
 ,m_NLBp(NLBp)
 ,m_NRUp(NRUp)
 ,m_NRBp(NRBp)
{

}

inline Frustum::~Frustum()
{

}
