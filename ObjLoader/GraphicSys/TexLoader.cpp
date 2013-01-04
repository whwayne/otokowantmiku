#include "TexLoader.h"
#include "../MikuCore/UtilStr.h"
#include "dds.h"


#define DDS_MAGIC 0x20534444
TexLoader::TexLoader()
{
	mTexDataInfo = new DDSTexDataInfo();
}

TexLoader::~TexLoader()
{
}

void TexLoader::LoadFromFile(const std::string& filePath)
{
	HANDLE hFile = CreateFile(filePath.c_str(),GENERIC_READ,0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if( INVALID_HANDLE_VALUE == hFile )
	{
	    return ;
	}
	LARGE_INTEGER FileSize = {0};
	GetFileSizeEx( hFile, &FileSize);

	if( FileSize.HighPart > 0 )
	{
	     CloseHandle( hFile );
		 return;
	}

	if( FileSize.LowPart < (sizeof(DDS_HEADER) + sizeof(DWORD)))
	{
		 CloseHandle( hFile );
		 return;
	}

	BYTE* HeapData = new BYTE [ FileSize.LowPart ];
	if(!HeapData)
	{
	   return;
	}

	DWORD BytesRead = 0;
	if( !ReadFile( hFile, HeapData, FileSize.LowPart, &BytesRead, NULL ) )
    {
        CloseHandle( hFile );
        return;
    }

	if( BytesRead < FileSize.LowPart )
    {
        CloseHandle( hFile );
        return;
    }

	DWORD dwMagicNumber = *( DWORD* )( HeapData );
    if( dwMagicNumber != DDS_MAGIC )
    {
        CloseHandle( hFile );
        return;
    }
	
	 mTexDataInfo->mDDS_HEADER = reinterpret_cast<DDS_HEADER*>( HeapData + sizeof( DWORD ) );

	 if( mTexDataInfo->mDDS_HEADER->dwSize != sizeof(DDS_HEADER)
        || mTexDataInfo->mDDS_HEADER->ddspf.dwSize != sizeof(DDS_PIXELFORMAT) )
    {
        CloseHandle( hFile );
        return;
    }
	
	bool bDXT10Header = false;
    if ( (mTexDataInfo->mDDS_HEADER->ddspf.dwFlags & DDS_FOURCC)
        && (MAKEFOURCC( 'D', 'X', '1', '0' ) == mTexDataInfo->mDDS_HEADER->ddspf.dwFourCC) )
    {
        // Must be long enough for both headers and magic value
        if( FileSize.LowPart < (sizeof(DDS_HEADER)+sizeof(DWORD)+sizeof(DDS_HEADER_DXT10)) )
        {
            CloseHandle( hFile );
            return;
        }

        bDXT10Header = true;
    }

	
    INT offset = sizeof( DWORD ) + sizeof( DDS_HEADER )
                 + (bDXT10Header ? sizeof( DDS_HEADER_DXT10 ) : 0);
	mTexDataInfo->mTexData = HeapData + offset;
	mTexDataInfo->mTexDataSize = FileSize.LowPart - offset;

    CloseHandle( hFile );
}

DDSTexDataInfo* 
TexLoader::GetTexDataInfo()
{
   return mTexDataInfo;
}