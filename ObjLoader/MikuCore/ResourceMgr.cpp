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
		AnsycGenerator<Loader,HardwareRes>* pAG = (AnsycGenerator<Loader,HardwareRes>*)(*iter);

		if (pAG->GetProcess()==AnsycGenerator<Loader,HardwareRes>::Complete)
		{
			ReplaceResource( pAG->GetPath(), *(pAG->GetRes()));

			std::list<ResGenerator*>::iterator deleteIter = iter;
			iter++;
			m_pResGenWaitingList.erase(deleteIter);
			o_delete(pAG);
		}
		else
		{
			iter++;
			continue;
		}
	}
	
}

void ResourceMgr::ReplaceResource( const std::string& ID,HardwareRes& res )
{
	std::map<std::string,Ptr<HardwareRes>> ::iterator iter = m_ID2ResDic.find(ID);
	if (iter!=m_ID2ResDic.end())
	{
		iter->second->Copy(res);
	}
}


