#pragma once

#include "D3D9SubMesh.h"
#include "ObjLoader.h"
#include <vector>

class D3D9Mesh:public D3D9Res
{
public:
	D3D9Mesh();
	virtual ~D3D9Mesh();

	
	virtual bool SetUp(Loader& loader);



	std::vector<Ptr<D3D9SubMesh>>& GetSubMeshArray()
	{
		return m_pSubMeshArray;
	}
protected:
	
	std::vector<Ptr<D3D9SubMesh>>      m_pSubMeshArray;
private:
};