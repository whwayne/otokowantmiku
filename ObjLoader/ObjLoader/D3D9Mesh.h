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

	virtual void Copy(D3D9Res& rhs);

// 	std::vector<Ptr<D3D9SubMesh>>& GetSubMeshArray()
// 	{
// 		return m_pSubMeshArray;
// 	}
	Ptr<D3D9SubMesh>* GetSubMeshArray()
	{
		return m_pSubMeshPtrArray;
	}

	int GetSubMeshCount()
	{
		return m_SubMeshCount;
	}
protected:
	
	Ptr<D3D9SubMesh>*   m_pSubMeshPtrArray;
	int                 m_SubMeshCount;
	//std::vector<Ptr<D3D9SubMesh>>      m_pSubMeshArray;
private:
};