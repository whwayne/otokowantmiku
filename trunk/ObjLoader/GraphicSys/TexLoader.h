#pragma once
#include "../MikuCore/Loader.h"
#include <vector>
#include "d3dx9.h"
#include "dds.h"

struct DDSTexDataInfo
{
    DDS_HEADER* mDDS_HEADER;
	BYTE* mTexData;
	unsigned int mTexDataSize;
};

class TexLoader: public Loader
{
public:
	TexLoader();
	~TexLoader();
	virtual void LoadFromFile(const std::string & filePath);
    DDSTexDataInfo* GetTexDataInfo();
protected:
	DDSTexDataInfo* mTexDataInfo;
private:

};