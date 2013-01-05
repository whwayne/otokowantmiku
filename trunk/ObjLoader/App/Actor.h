#pragma once
#include "..\MikuCore\Res.h"
#include "..\MikuCore\Ptr.h"
#include "..\MikuCore\RttiMacros.h"
#include "Component.h"
#include <vector>

namespace FrameWork
{
	class Actor:public Res
	{
		__DeclareClass(Actor)
	public:
		Actor();
		virtual ~Actor();

		void AttachComponent(const Ptr<Component>& com);
	protected:
		std::vector<Ptr<Component>> m_arrComponent;

	};
}
