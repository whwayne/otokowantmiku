#pragma once
#include "Ptr.h"
#include "Res.h"
#include <map>
#include <string>


class ResourceMgr
{
public:
	static ResourceMgr& GetInstance()
	{
		static ResourceMgr instance;
		return instance;
	}
	virtual ~ResourceMgr();
	
	Ptr<Res> GetResByID(const std::string& ID);


	template<typename T>
	void CreateRes(const std::string path);
	
protected:
	ResourceMgr();

protected:
	std::map<std::string,Ptr<Res>> m_ID2ResDic;

};

template<typename T>
void ResourceMgr::CreateRes( const std::string path )
{

}
