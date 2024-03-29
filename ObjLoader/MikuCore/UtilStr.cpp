#include "UtilStr.h"

std::vector<std::string> Util_StrToken(std::string Str,const std::string& Token )
{
	std::vector<std::string> result;
	
	char *p;
	p = strtok(const_cast<char*>( Str.c_str() ),Token.c_str() );
	while(p)
	{
		result.push_back(std::string(p));
	    p=strtok(NULL,Token.c_str());
	}
	return result;
}
