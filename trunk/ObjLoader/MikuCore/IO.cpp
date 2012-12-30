#include "IO.h"

void* IO::OpenFile( const std::string& path )
{
	void* hFile = CreateFile(path.c_str(),GENERIC_READ,0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return hFile;
}

unsigned int IO::GetFileSize( void* handle )
{
	return  ::GetFileSize(handle,NULL);
}

void IO::ReadFile( void* handle,void* buffer,unsigned int size )
{
	DWORD dwBytesRead = 0;
	::ReadFile(handle,buffer, size, &dwBytesRead, NULL);
}

IO::IO()
{

}

IO::~IO()
{

}
