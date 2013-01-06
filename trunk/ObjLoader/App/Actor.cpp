#include "Actor.h"

namespace FrameWork
{
	__ImplementClass(Actor,'ACTR',Res)

	Actor::Actor()
	:m_arrComponent()
	{

	}

	Actor::~Actor()
	{

	}


	void Actor::OnFrame( float deltaTime )
	{
		for (int i = 0; i<m_arrComponent.size();i++ )
		{
			m_arrComponent[i]->OnFrame(deltaTime);
		}
	}


	void Actor::AttachComponent( const Ptr<Component>& com )
	{
		m_arrComponent.push_back(com);
	}

}