#pragma once
#include <string>
#include <Windows.h>

class IO
{
public:
	static IO& GetInstance()
	{
		static IO instance;
		return instance;
	}
	virtual ~IO();

	void* OpenFile(const std::string& path);
	unsigned int GetFileSize(void* handle);
	void ReadFile(void* handle,void* buffer,unsigned int size);

protected:
	IO();
};