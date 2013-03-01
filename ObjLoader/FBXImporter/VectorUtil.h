#pragma once
#include <vector>
#include <windows.h>

template<typename T>
int VectorFind(std::vector<T>& vec,T value)
{
	for (unsigned int i =0;i<vec.size();i++)
	{
		if ( vec[i]==value )
		{
			return i;
		}
	}
	return -1;
}

void __cdecl Format(const char* out,const char* fmtString, ...);

void __cdecl Format(const char* out,int bufflength,const char* fmtString, ...);