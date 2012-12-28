#include "AABBox.h"
#include "Matrix44.h"

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

InterSectResult aabbox::InterSect( const matrix44& viewProj )
{
	std::vector<point> rPoints = FormPoint();
	unsigned int AddFlags = 0xffff;
	unsigned int OrFlags  = 0;
	point pl;
	for (int i = 0;i<(int)rPoints.size();i++)
	{
		unsigned int clip = 0;
		pl = viewProj*rPoints[i];
		if (pl.X()<-pl.W())
		{
			clip |= 1<<0;
		}
		if (pl.X()>pl.W())
		{
			clip |= 1<<1;
		}
		if (pl.Y()<-pl.W())
		{
			clip |= 1<<2;
		}
		if (pl.Y()>pl.W())
		{
			clip |= 1<<3;
		}
		if (pl.Z()>pl.W())
		{
			clip |= 1<<4;
		}
		if ( pl.Z()<0.f )
		{
			clip |= 1<<5;
		}
		AddFlags &= clip;
		OrFlags  |= clip;
	}
	if (OrFlags == 0)
	{
		return INTERSECTIN;
	}
	if (AddFlags!=0)
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

	rPoints[0] = middle+point( halfX,-halfY,-halfZ,0.f );
	rPoints[1] = middle+point(-halfX,-halfY,-halfZ,0.f );
	rPoints[2] = middle+point( halfX,-halfY,halfZ,0.f );
	rPoints[3] = middle+point(-halfX,-halfY,halfZ,0.f );
	rPoints[4] = middle+point( halfX,halfY,-halfZ,0.f );
	rPoints[5] = middle+point( -halfX,halfY,-halfZ,0.f );
	rPoints[6] = middle+point( halfX,halfY, halfZ,0.f );
	rPoints[7] = middle+point( -halfX,halfY,halfZ,0.f );

	return rPoints;
}

aabbox aabbox::Transform( const matrix44& mtra )
{
	point pMax(-999999.f,-999999.f,-999999.f,1.f);
	point pMin( 999999.f, 999999.f, 999999.f,1.f);

	point pl;
	std::vector<point> rPoints = FormPoint();

	matrix44 pointPos;
	for ( int i =0 ; i< (int)rPoints.size(); i++ )
	{
		pointPos = matrix44::IDENTITY;
		pointPos.makeTransLH(rPoints[i]);
		pointPos = mtra*pointPos;

		pl = float4(pointPos[3][0],pointPos[3][1],pointPos[3][2],1.f);

		pMax.X() = Max(pMax.X(),pl.X());
		pMax.Y() = Max(pMax.Y(),pl.Y());
		pMax.Z() = Max(pMax.Z(),pl.Z());

		pMin.X() = Min(pMin.X(),pl.X());
		pMin.Y() = Min(pMin.Y(),pl.Y());
		pMin.Z() = Min(pMin.Z(),pl.Z());
	}
	return aabbox(pMax,pMin);
}
