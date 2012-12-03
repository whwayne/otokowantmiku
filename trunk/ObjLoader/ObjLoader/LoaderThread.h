#pragma once
#include <list>
#include "CriticalSection.h"
#include "Thread.h"
#include "ResGenerator.h"
#include "AnsycGenerator.h"

class LoaderThread:public Thread
{
public:
	LoaderThread();
	virtual ~LoaderThread();
	
	void PushResGenerator(ResGenerator* pResGenerator)
	{
		m_CriticalSection.Enter();
		m_pResGeneratorList.push_back(pResGenerator);
		m_CriticalSection.Leave();
	}

	//this function is used to pop a ResGenerator* out
	ResGenerator* PopResGenerator(ResGenerator* pResGenerator)
	{
		m_CriticalSection.Enter();
		std::list<ResGenerator*>::iterator iter;
		for (iter = m_pResGeneratorList.begin();iter!=m_pResGeneratorList.end();iter++)
		{
			if ((*iter)==pResGenerator)
			{
				m_pResGeneratorList.erase(iter);
				break;
			}
		}	
		m_CriticalSection.Leave();
	}
protected:
	virtual void DoWork();
protected:
	std::list<ResGenerator*> m_pResGeneratorList;//this should be a quee,but i use list here instead.
protected:
	CriticalSection m_CriticalSection;
private:
};