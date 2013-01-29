#pragma once
#include <vector>

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