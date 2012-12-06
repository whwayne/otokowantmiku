#include "ResourceMgr.h"
#include "AnsycGenerator.h"

ResourceMgr::ResourceMgr()
:m_ID2ResDic()
,m_pResGenWaitingList()
{

}


ResourceMgr::~ResourceMgr()		
{

}



void ResourceMgr::OnBeginFrame()
{
	std::list<ResGenerator*>::iterator iter = m_pResGenWaitingList.begin();
	for(;iter!=m_pResGenWaitingList.end();)
	{
		AnsycGenerator<Loader,D3D9Res>* pAG = (AnsycGenerator<Loader,D3D9Res>*)(*iter);

		if (pAG->GetProcess()==AnsycGenerator<Loader,D3D9Res>::Complete)
		{
			ReplaceResource( pAG->GetPath(), *(pAG->GetRes()));

			std::list<ResGenerator*>::iterator deleteIter = iter;
			iter++;
			m_pResGenWaitingList.erase(deleteIter);
			delete pAG;
		}
		else
		{
			iter++;
			continue;
		}
	}
	
}

void ResourceMgr::ReplaceResource( const std::string& ID,D3D9Res& res )
{
	std::map<std::string,Ptr<D3D9Res>> ::iterator iter = m_ID2ResDic.find(ID);
	if (iter!=m_ID2ResDic.end())
	{
		iter->second->Copy(res);
	}
}


