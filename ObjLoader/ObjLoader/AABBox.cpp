#include "AABBox.h"

InterSectResult aabbox::InterSect( aabbox& box )
{

	if ((this->mMax.X()>box.mMax.X()&&this->mMax.Y()>box.mMax.Y()&&this->mMax.Z()>box.mMax.Z() )&&(this->mMin.X()<box.mMin.X()&&this->mMin.Y()<box.mMin.Y()&&this->mMin.Z()<box.mMin.Z() ))
	{
		return INTERSECTIN;
	}
	else if ( (this->mMax.X()<box.mMin.X() ||this->mMin.X()>box.mMax.X() )||(this->mMax.Y()<box.mMin.Y() ||this->mMin.Y()>box.mMax.Y() )||(this->mMax.Z()<box.mMin.Z() ||this->mMin.Z()>box.mMax.Z() ))
	{
		return INTERSECTOUT;
	}
	else
	{
		return INTERSECTPART;
	}
}

std::vector<point> aabbox::FormPoint()
{
	std::vector<point> rPoints;
	rPoints.resize(8);


	point middle = (mMax+mMin)*0.5f;
	scalar halfX = mMax.X()-middle.X();
	scalar halfY = mMax.Y()-middle.Y();
	scalar halfZ = mMax.Z()-middle.Z();

	rPoints[0] = middle+point( halfX,-halfY,-halfZ,1.f );
	rPoints[1] = middle+point(-halfX,-halfY,-halfZ,1.f );
	rPoints[2] = middle+point( halfX,-halfY,halfZ,1.f );
	rPoints[3] = middle+point(-halfX,-halfY,halfZ,1.f );
	rPoints[4] = middle+point( halfX,halfY,-halfZ,1.f );
	rPoints[5] = middle+point( -halfX,halfY,-halfZ,1.f );
	rPoints[6] = middle+point( halfX,halfY, halfZ,1.f );
	rPoints[7] = middle+point( -halfX,halfY,halfZ,1.f );

	return rPoints;
}
