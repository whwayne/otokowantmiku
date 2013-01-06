#pragma once
#include "..\MikuCore\RttiMacros.h"
#include "..\ScriptFeature\ScriptBind.h"
#include "Actor.h"


namespace FrameWork
{
	class ActorMgr
	{
		__DeclareClass(ActorMgr)
		__Scriptbind
	public:
		static ActorMgr& GetInstance()
		{
			static ActorMgr instance;
			return instance;
		}
		virtual ~ActorMgr();

		void OnFrame(float deltaTime);
	

		void AttachActors(const Ptr<Actor>& act);
	protected:
		ActorMgr();

	protected:
		std::vector<Ptr<Actor>> m_arrActor;
	};
}