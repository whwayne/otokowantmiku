#pragma once
#include "../MikuCore/Loader.h"
#include "Memory.h"
#include "D3D9VertexComponent.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include <string>
#include <vector>

struct ObjSubMeshContent 
{
	ObjSubMeshContent()
	{

	}
	std::vector<float> mVertexPos;
	std::vector<float> mVertexUV;
	std::vector<float> mVertexNormal;
	std::vector<int> mVertexIndexBuffer;
	std::vector<float> mVertexBuffer;
	std::vector<D3D9VertexComponent::Type> mVertexLayout;
};




class ObjLoader:public Loader
{
public:
	ObjLoader();
	virtual ~ObjLoader();

	void LoadFromFile(const std::string& path);

	std::vector<ObjSubMeshContent>& GetContent()
	{
		return mSubMeshContent;
	}

protected:

	std::vector<ObjSubMeshContent> mSubMeshContent;
private:
};