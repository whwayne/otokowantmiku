#pragma once
#include <string>

class Loader
{
public:
	Loader();
	virtual ~Loader();
	void LoadFromFile(const std::string& path);
protected:
private:
};