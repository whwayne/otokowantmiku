#pragma once
#include "..\MikuCore\Res.h"
#include "..\MikuCore\Ptr.h"
#include "..\MikuCore\RttiMacros.h"


namespace FrameWork
{
	class Actor;
	class Component:public Res
	{
		__DeclareClass(Component)
	public:
		Component();
		virtual ~Component();

		virtual void SetActor(Actor* pAct);

		virtual void OnFrame(float deltaTime) {};
	protected:
		Actor* m_pAct;
	};

	inline void Component::SetActor( Actor* pAct )
	{
		m_pAct = pAct;
	}

}