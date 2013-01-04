#pragma once
#include "..\MikuCore\Res.h"
#include "..\MikuCore\Ptr.h"
#include "..\MikuCore\RttiMacros.h"


namespace FrameWork
{
	class Component:public Res
	{
		__DeclareClass(Component)
	public:
		Component();
		virtual ~Component();
	protected:
	};
}