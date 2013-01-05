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

	void Actor::AttachComponent( const Ptr<Component>& com )
	{
		m_arrComponent.push_back(com);
	}

}