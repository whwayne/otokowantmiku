#include <Windows.h>




class Res
{
public:
	Res()
		:m_Ref(0)
	{

	}
	virtual ~Res()
	{

	}
	void AddRef()
	{
		m_Ref++;
	}
	void Release()
	{
		m_Ref--;
		if (m_Ref==0)
		{
			delete this;
		}
	}


protected:
	int m_Ref;




private:
};