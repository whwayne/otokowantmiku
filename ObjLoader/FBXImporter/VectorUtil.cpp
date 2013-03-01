#include "VectorUtil.h"
#include <strsafe.h>
void __cdecl Format( const char* out,const char* fmtString, ... )
{
	va_list argList;
	va_start(argList, fmtString);
	
	// need to use non-CRT thread safe function under Win32
	StringCchVPrintf((char*)out, sizeof(out), fmtString, argList);

	va_end(argList);
}

void __cdecl Format( const char* out,int bufflength,const char* fmtString, ... )
{
	va_list argList;
	va_start(argList, fmtString);

	// need to use non-CRT thread safe function under Win32
	StringCchVPrintf((char*)out, bufflength, fmtString, argList);

	va_end(argList);
}
