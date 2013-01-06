#pragma once
#include "ActorManager.h"
#include "..\MikuCore\ResourceMgr.h"


namespace FrameWork
{
	class GameApp
	{
	public:
		static GameApp& GetInstance()
		{
			static GameApp instance;
			return instance;
		}
		void SetUp( HWND hWnd );

		void OnBeginFrame(float deltaTime);

		void OnFrame(float deltaTime);

		void Exit();

		void BackGroundTick(float deltaTime);

		virtual	~GameApp();
	protected:


		void OnRender(float deltaTime);
		GameApp();
	};
}

