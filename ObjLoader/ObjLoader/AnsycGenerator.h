#pragma once
#include <string>
#include <assert.h>
#include "Memory.h"
#include "Loader.h"
#include "D3D9Res.h"
#include "ResGenerator.h"

//this is a warpper class of loaders and res for the muti thread loading

template<typename tLoader,typename tRes> 
class AnsycGenerator: public ResGenerator
{
public:
	enum Process
	{
		Prepared = 0,
		Processing,
		Complete,
	};
public:
	AnsycGenerator()
		:m_pLoader(NULL)
		,m_pRes(NULL)
		,m_Process(Prepared)
		,m_path()
	{
		
	}
	virtual ~AnsycGenerator()
	{
		// do not delete the res ptr, because the main thread is using it now!
	}

	tRes* GetRes()
	{
		return m_pRes;
	}

	void SetPath(const std::string& path)
	{
		m_path = path;
	}
	std::string& GetPath()
	{
		return m_path;
	}

	Process GetProcess()
	{
		return m_Process;

	}
	virtual Res* GeneratorRes(const std::string& path);
protected:
	tLoader*			m_pLoader;
	tRes*				m_pRes;
	volatile Process    m_Process;
	std::string			m_path;
private:
};

template<typename tLoader,typename tRes>
Res* AnsycGenerator<tLoader, tRes>::GeneratorRes( const std::string& path )
{
	assert(strcmp(path.c_str(),"")==0);
	m_Process = Processing;

	m_pLoader = o_new(tLoader);
	m_pLoader->LoadFromFile(m_path);

	m_pRes    = o_new(tRes);
	m_pRes->SetUp(*m_pLoader);

	o_delete(m_pLoader);
	m_pLoader = NULL;

	m_Process = Complete;

	return m_pRes;
}
