#include "UtilStr.h"

std::vector<std::string> Util_StrToken(const std::string& Str,std::string& Token )
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
