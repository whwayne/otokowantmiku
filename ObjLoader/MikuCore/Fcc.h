/*
the only ID for each type we declare
*/
#pragma once 

class Fcc
{
public:
	Fcc():m_fcc(0)
	{}
	Fcc(unsigned int fcc):m_fcc(fcc)
	{

	}
	Fcc(const char* fcc)
	{
		m_fcc = ( (unsigned int)fcc[3] >> 24 | (unsigned int)fcc[2] >> 16 | (unsigned int)fcc[1] >> 8| (unsigned int)fcc );
	}

	~Fcc(){}

private:
	unsigned int m_fcc;
};

