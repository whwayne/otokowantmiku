#include "ActorManager.h"

namespace FrameWork
{
	__ImplementClass(ActorMgr,'ATMR',NULL)

	ActorMgr::ActorMgr()
		:m_arrActor()
	{

	}

	ActorMgr::~ActorMgr()
	
	{

	}

	
	void ActorMgr::AttachActors( const Ptr<Actor>& act )
	{
		m_arrActor.push_back(act);
	}

	void ActorMgr::OnFrame( float deltaTime )
	{
		for (int i = 0;i<m_arrActor.size();i++)
		{
			m_arrActor[i]->OnFrame(deltaTime);
		}
	}


}