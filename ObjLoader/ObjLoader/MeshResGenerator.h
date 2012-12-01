#pragma once
#include "ResGenerator.h"
#include "D3D9Mesh.h"
#include "ObjLoader.h"
#include "Memory.h"

class MeshResGenerator:public ResGenerator
{
public:
	MeshResGenerator();
	virtual ~MeshResGenerator();
	virtual  Res* GeneratorRes(const std::string& path);
protected:
private:
};