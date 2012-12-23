#include "AABBox.h"

InterSectResult aabbox::InterSect( aabbox& box )
{
	if ((this->mMax.X()>box.mMax.X()&&this->mMax.Y()>box.mMax.Y()&&this->mMax.Z()>box.mMax.Z() )&&(this->mMin.X()<box.mMin.X()&&this->mMin.Y()<box.mMin.Y()&&this->mMin.Z()<box.mMin.Z() ))
	{
		return INTERSECTIN;
	}
	else if ( (this->mMax.X()<box.mMin.X() && this->mMax.Y()<box.mMin.Y() && this->mMax.Z()<box.mMin.Z() ) &&( (this->mMin.X()>box.mMax.X() && this->mMin.Y()>box.mMax.Y() && this->mMin.Z()>box.mMax.Z() )))
	{
		return INTERSECTOUT;
	}
	else
	{
		return INTERSECTPART;
	}
}
