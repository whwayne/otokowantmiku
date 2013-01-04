#pragma once
#include "../MikuCore/ResGenerator.h"
#include "D3D9Mesh.h"
#include "ObjLoader.h"
#include "Memory.h"
//this is almost same as ansycloader,but it's not for the muti thread
class MeshResGenerator:public ResGenerator
{
public:
	MeshResGenerator();
	virtual ~MeshResGenerator();
	virtual  Res* GeneratorRes(const std::string& path);
protected:
private:
};