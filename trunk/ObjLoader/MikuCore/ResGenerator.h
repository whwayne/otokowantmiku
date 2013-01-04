#pragma once
#include <Windows.h>
#include <string>
#include "Loader.h"
#include "Res.h"


class ResGenerator
{
public:
	ResGenerator();
	virtual ~ResGenerator();
	virtual Res* GeneratorRes(const std::string& path);
protected:
private:
};