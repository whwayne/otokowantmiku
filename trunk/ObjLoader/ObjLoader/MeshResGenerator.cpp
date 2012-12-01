#include "MeshResGenerator.h"

MeshResGenerator::MeshResGenerator()
{

}

MeshResGenerator::~MeshResGenerator()
{

}

Res* MeshResGenerator::GeneratorRes( const std::string& path )
{
	ObjLoader* pLoader = o_new(ObjLoader);

	pLoader->LoadFromFile(path);

	D3D9Mesh* pMesh = o_new(D3D9Mesh);

	pMesh->SetUp(*pLoader);

	o_delete(pLoader);
	pLoader = NULL;

	return pMesh;
}

