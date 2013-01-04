#include "MathDefine.h"


Radian ACos( scalar fValue )
{
	if ( -1.0 < fValue )
	{
		if ( fValue < 1.0 )
			return Radian(acos(fValue));
		else
			return Radian(0.0);
	}
	else
	{
		return Radian(PI);
	}
}

Radian ASin( scalar fValue )
{
	if ( -1.0 < fValue )
	{
		if ( fValue < 1.0 )
			return Radian(asin(fValue));
		else
			return Radian(HALF_PI);
	}
	else
	{
		return Radian(-HALF_PI);
	}
}

