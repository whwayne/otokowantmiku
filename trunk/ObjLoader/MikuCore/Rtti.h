/*
run time type identification for all the classes we write,
all the classes will obtain it

edit by zhaoxiaohang 12.6.23  1.0v
*/
#pragma once 
#include "Fcc.h"

namespace Core
{
	class Rtti
	{
	public:
		Rtti()
			:m_fcc()
			,m_typeName(0)
		{}
		Rtti(Fcc fcc,const char* typeName)
			:m_fcc(fcc)
			,m_typeName(typeName)
		{}

		~Rtti()
		{
			m_typeName = 0;
		}

		const char* GetTypeName() const
		{
			return m_typeName;
		}
	private:
		Fcc m_fcc;
		const char* m_typeName;
	};

}