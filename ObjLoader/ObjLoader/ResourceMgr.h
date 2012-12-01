#pragma once
#include "Ptr.h"
#include "Res.h"
#include <map>
#include <string>
#include "Memory.h"
#include "ResGenerator.h"
#include "MeshResGenerator.h"

class ResourceMgr
{
public:
	static ResourceMgr& GetInstance()
	{
		static ResourceMgr instance;
		return instance;
	}
	virtual ~ResourceMgr();

	template<typename T>
	Ptr<Res> GetResByID(const std::string& ID);
		
protected:
	template<typename T>
	void CreateRes(const std::string& path);

	ResourceMgr();

protected:
	std::map<std::string,Ptr<Res>> m_ID2ResDic;

};
template<typename T>
Ptr<Res> ResourceMgr::GetResByID( const std::string& ID )
{
	std::map<std::string,Ptr<Res>> ::iterator iter = m_ID2ResDic.find(ID);
	if (iter!=m_ID2ResDic.end())
	{
		return iter->second;
	}
	else
	{
		CreateRes<T>(ID);
		return GetResByID<T>(ID);
	}
}

template<typename T>
void ResourceMgr::CreateRes( const std::string& path )
{
	T* pResGenerator= o_new(T);
	Res* pRes = pResGenerator->GeneratorRes(path);
	o_delete(pResGenerator);
	m_ID2ResDic.insert(std::pair<std::string,Ptr<Res>>(path,pRes));
}
