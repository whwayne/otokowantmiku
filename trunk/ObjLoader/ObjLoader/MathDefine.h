#pragma once
#include <Windows.h>
#include <math.h>
#include <stdio.h>

typedef float scalar;

#define o_abs(t) std::abs(t)

#define o_sqrt(t) sqrt(t)



inline bool RealEqual( scalar a, scalar b, scalar tolerance )
{
	if (fabs(b-a) <= tolerance)
		return true;
	else
		return false;
}