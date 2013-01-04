#pragma once
#include "Ptr.h"
#include "Res.h"
#include <map>
#include <string>
#include "ResGenerator.h"
#include "../GraphicSys/MeshResGenerator.h"
#include "LoaderThread.h"

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

	template<typename tLoader,typename tRes> 
	Ptr<Res> GetResAnsycByID(const std::string& ID);
		

	void OnBeginFrame();
protected:
	template<typename T>
	void CreateRes(const std::string& path);

	template<typename tLoader,typename tRes> 
	void CreateResAnsyc(const std::string& path);

	void ReplaceResource(const std::string& ID,	D3D9Res& res);

	ResourceMgr();

protected:
	std::map<std::string,Ptr<D3D9Res>> m_ID2ResDic;
	std::list<ResGenerator*>       m_pResGenWaitingList;

};

template<typename tLoader,typename tRes> 
Ptr<Res> ResourceMgr::GetResAnsycByID( const std::string& ID )
{
	std::map<std::string,Ptr<D3D9Res>> ::iterator iter = m_ID2ResDic.find(ID);
	if (iter!=m_ID2ResDic.end())
	{
		return iter->second.downcast<Res>();
	}
	else
	{
		CreateResAnsyc<tLoader,tRes>(ID);

		Ptr<D3D9Res> pRes = o_new(tRes);
		m_ID2ResDic.insert(std::pair<std::string,Ptr<D3D9Res>>(ID,pRes));
		return pRes.cast<Res>();
	}
}


template<typename tLoader,typename tRes>
void ResourceMgr::CreateResAnsyc( const std::string& path )
{
	//ResGenerator* pResGenerator= o_new2( AnsycGenerator<tLoader,tRes> );
	typedef AnsycGenerator<tLoader,tRes> BaseAnsycGenerator;
	ResGenerator* pResGenerator= o_new(BaseAnsycGenerator);
	AnsycGenerator<tLoader,tRes>* pAnsycGenerator=(AnsycGenerator<tLoader,tRes>*)pResGenerator;
	pAnsycGenerator->SetPath(path);
	LoaderThread::GetInstance().PushResGenerator(pResGenerator);
	m_pResGenWaitingList.push_back(pResGenerator);
}

template<typename T>
Ptr<Res> ResourceMgr::GetResByID( const std::string& ID )
{
	std::map<std::string,Ptr<D3D9Res>> ::iterator iter = m_ID2ResDic.find(ID);
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
	m_ID2ResDic.insert(std::pair<std::string,Ptr<D3D9Res>>(path,pRes));
}
