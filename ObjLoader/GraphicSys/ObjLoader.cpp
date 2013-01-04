#include "ObjLoader.h"
#include "..\MikuCore\UtilStr.h"

struct VertexCacheUnit
{
	VertexCacheUnit(int pos,int uv,int normal)
	{
		vPos = pos;
		vUV = uv;
		vNormal = normal;
	}
	bool Compare(VertexCacheUnit& rhs)
	{
		if (rhs.vNormal==vNormal&&rhs.vPos==vPos&&rhs.vUV==vUV)
		{
			return true;
		}
		return false;
	}
	int vPos;
	int vUV;
	int vNormal;
};


ObjLoader::ObjLoader()
{

}

ObjLoader::~ObjLoader()
{

}

void ObjLoader::LoadFromFile(const std::string& path )
{

	std::vector<VertexCacheUnit> vertexCache;

	void* hFile = CreateFile(path.c_str(),GENERIC_READ,0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	SetFilePointer(hFile,0,0,	FILE_BEGIN );
	int fileSize = GetFileSize(hFile,NULL);

	DWORD dwBytesRead = 0;

	void* ReadBuffer = o_newArray(char,fileSize+1);
	ReadFile(hFile,ReadBuffer, fileSize+1, &dwBytesRead, NULL);

	int iSubMeshIndex = -1;
	int iVertexIndex  = -1;
	
	std::string sWholeFile((char*)ReadBuffer);
	std::vector<std::string> strLines = Util_StrToken(sWholeFile,std::string("\n"));
	
	std::string lastHead;

	for (unsigned int iline = 0;iline<strLines.size();iline++)
	{
		std::vector<std::string> strUnits = Util_StrToken(strLines[iline],std::string(" "));
		if( 0 == strcmp( strUnits[0].c_str(), "#" ) )
		{
			 //- # means explanatory notes in .obj file.
			continue;
		}
		
		else if ( 0 == strcmp( strUnits[0].c_str(), "g" ) )
		{
			
		
		}

		if (0 == strcmp( strUnits[0].c_str(), "v" ))
		{
			if (0 != strcmp( lastHead.c_str(), "v" ))
			{
				// this meams a submesh start.
				vertexCache.clear();
				iSubMeshIndex++;
				iVertexIndex = -1;
				mSubMeshContent.push_back(ObjSubMeshContent());
			}
			//- v means the position of the vertices.
			mSubMeshContent[iSubMeshIndex].mVertexPos.push_back(atof(strUnits[1].c_str()));
			mSubMeshContent[iSubMeshIndex].mVertexPos.push_back(atof(strUnits[2].c_str()));
			mSubMeshContent[iSubMeshIndex].mVertexPos.push_back(atof(strUnits[3].c_str()));
		}
		else if (0 == strcmp( strUnits[0].c_str(), "vt" ))
		{
			//- vt means the uv of the vertices
			mSubMeshContent[iSubMeshIndex].mVertexUV.push_back(atof(strUnits[1].c_str()));
			mSubMeshContent[iSubMeshIndex].mVertexUV.push_back(atof(strUnits[2].c_str()));
		}
		else if (0 == strcmp( strUnits[0].c_str(), "vn" ))
		{
			//- vt means the normal of the vertices
			mSubMeshContent[iSubMeshIndex].mVertexNormal.push_back(atof(strUnits[1].c_str()));
			mSubMeshContent[iSubMeshIndex].mVertexNormal.push_back(atof(strUnits[2].c_str()));
			mSubMeshContent[iSubMeshIndex].mVertexNormal.push_back(atof(strUnits[3].c_str()));
		}
		else if ( 0== strcmp( strUnits[0].c_str(), "f" ))
		{
			//- f means the true vertex comes!
			for (int iCurentIndex=0;iCurentIndex<3;iCurentIndex++)
			{
				std::vector<std::string> strVtxCpn = Util_StrToken( strUnits[iCurentIndex+1],std::string("/") );
				int vPosIndex = atoi(strVtxCpn[0].c_str())-1;
				int vUVIndex = atoi(strVtxCpn[1].c_str())-1;
				int vNormalIndex = atoi(strVtxCpn[2].c_str())-1;

				//-the fucking obj file's submesh vertex index is not restart from 0,so I have to do the fucking thing below;  
				for (int i = 0;i<iSubMeshIndex; i++)
				{
					vPosIndex = vPosIndex - mSubMeshContent[i].mVertexPos.size()/3;
					vUVIndex = vUVIndex - mSubMeshContent[i].mVertexUV.size()/2;
					vNormalIndex = vNormalIndex - mSubMeshContent[i].mVertexNormal.size()/3;
				}

				VertexCacheUnit chace(vPosIndex,vUVIndex,vNormalIndex);
				int storagedIndex = -1;
				for ( int i=0; i<vertexCache.size(); i++ )
				{
					if ( vertexCache[i].Compare(chace) )
					{
						storagedIndex = i;
						break;
					}
				}

				if ( storagedIndex!=-1 )
				{
					//- if the vertex has already be storged,just use it
					mSubMeshContent[iSubMeshIndex].mVertexIndexBuffer.push_back(storagedIndex);
				}
				else
				{
					mSubMeshContent[iSubMeshIndex].mVertexLayout.clear();
					//- if vertex can't be found ,create a new one and push it into the cache. 
					//- POS
					mSubMeshContent[iSubMeshIndex].mVertexBuffer.push_back(mSubMeshContent[iSubMeshIndex].mVertexPos[vPosIndex*3]);
					mSubMeshContent[iSubMeshIndex].mVertexBuffer.push_back(mSubMeshContent[iSubMeshIndex].mVertexPos[vPosIndex*3+1]);
					mSubMeshContent[iSubMeshIndex].mVertexBuffer.push_back(mSubMeshContent[iSubMeshIndex].mVertexPos[vPosIndex*3+2]);
					mSubMeshContent[iSubMeshIndex].mVertexLayout.push_back(D3D9VertexComponent::COM_POSITION);
					//-NORMAL
					mSubMeshContent[iSubMeshIndex].mVertexBuffer.push_back(mSubMeshContent[iSubMeshIndex].mVertexNormal[vNormalIndex*3]);
					mSubMeshContent[iSubMeshIndex].mVertexBuffer.push_back(mSubMeshContent[iSubMeshIndex].mVertexNormal[vNormalIndex*3+1]);
					mSubMeshContent[iSubMeshIndex].mVertexBuffer.push_back(mSubMeshContent[iSubMeshIndex].mVertexNormal[vNormalIndex*3+1]);
				    mSubMeshContent[iSubMeshIndex].mVertexLayout.push_back(D3D9VertexComponent::COM_NORMAL);
					//-UV
					mSubMeshContent[iSubMeshIndex].mVertexBuffer.push_back(mSubMeshContent[iSubMeshIndex].mVertexUV[vUVIndex*2]);
					mSubMeshContent[iSubMeshIndex].mVertexBuffer.push_back(mSubMeshContent[iSubMeshIndex].mVertexUV[vUVIndex*2+1]);
					mSubMeshContent[iSubMeshIndex].mVertexLayout.push_back(D3D9VertexComponent::COM_UV);
					
					//- storge a vertex for the check later
					vertexCache.push_back(chace);

					//- write the index.
					iVertexIndex += 1;
					mSubMeshContent[iSubMeshIndex].mVertexIndexBuffer.push_back(iVertexIndex);
				}
			}
		}
		lastHead = strUnits[0];
	}
	o_deleteArray(ReadBuffer);
}
