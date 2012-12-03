#include "LoaderThread.h"


LoaderThread::LoaderThread()
	:m_CriticalSection()
	,m_pResGeneratorList()
{

}

LoaderThread::~LoaderThread()
{

}

void LoaderThread::DoWork()
{
	while (1)//run always,if no res need to load ,just keep running
	{
		if (m_pResGeneratorList.size()==0)
		{
			continue;
		}

		m_CriticalSection.Enter();
		std::list<ResGenerator*>::iterator iter = m_pResGeneratorList.begin();
		m_CriticalSection.Leave();

		(*iter)->GeneratorRes(NULL);

		m_CriticalSection.Enter();
		m_pResGeneratorList.erase(iter);
		m_CriticalSection.Leave();
	}
}


