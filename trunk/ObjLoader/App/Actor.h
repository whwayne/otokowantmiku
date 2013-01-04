#pragma once
#include "..\MikuCore\Res.h"
#include "..\MikuCore\Ptr.h"
#include "..\MikuCore\RttiMacros.h"


namespace FrameWork
{
	class Actor:public Res
	{
		__DeclareClass(Actor)
	public:
		Actor();
		virtual ~Actor();
	protected:

	};
}
