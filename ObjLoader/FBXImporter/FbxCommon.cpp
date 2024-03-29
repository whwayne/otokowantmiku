#include "FbxCommon.h"

#include "VectorUtil.h"

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;


#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pManager->GetIOSettings()))
#endif

void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene)
{
	//The first thing to do is to create the FBX Manager which is the object allocator for almost all the classes in the SDK
	pManager = FbxManager::Create();
	if( !pManager )
	{
		FBXSDK_printf("Error: Unable to create FBX Manager!\n");
		exit(1);
	}
	else FBXSDK_printf("Autodesk FBX SDK version %s\n", pManager->GetVersion());

	//Create an IOSettings object. This object holds all import/export settings.
	FbxIOSettings* ios = FbxIOSettings::Create(pManager, IOSROOT);
	pManager->SetIOSettings(ios);

	//Load plugins from the executable directory (optional)
	FbxString lPath = FbxGetApplicationDirectory();
	pManager->LoadPluginsDirectory(lPath.Buffer());

	//Create an FBX scene. This object holds most objects imported/exported from/to files.
	pScene = FbxScene::Create(pManager, "My Scene");
	if( !pScene )
	{
		FBXSDK_printf("Error: Unable to create FBX scene!\n");
		exit(1);
	}
}

void DestroySdkObjects( FbxManager* pManager, bool pExitStatus )
{
	//Delete the FBX Manager. All the objects that have been allocated using the FBX Manager and that haven't been explicitly destroyed are also automatically destroyed.
	if( pManager ) pManager->Destroy();
	if( pExitStatus ) FBXSDK_printf("Program Success!\n");
}

void LoadScene(FbxManager* pManager,FbxScene*& pScene, const char* fileName)
{
	FbxImporter* sceneImporter = FbxImporter::Create(pManager,"");
	sceneImporter->Initialize(fileName,-1,pManager->GetIOSettings());
	sceneImporter->Import(pScene);
	sceneImporter->Destroy();
}


void WalkHierarchy(const FbxScene* pScene)
{
	FbxNode* root = pScene->GetRootNode();
	for (int i=0;i<root->GetChildCount();i++)
	{
		WalkHierarchy(root->GetChild(i));
	}
}

void WalkHierarchy(FbxNode *fbxNode)
{    
	FbxNodeAttribute* nodeAtt = fbxNode->GetNodeAttribute();
	std::string out;
	if(nodeAtt == NULL)
	{
		printf("null node");
	}
	else
	{
		
		switch (nodeAtt->GetAttributeType())
		{
		case FbxNodeAttribute::eMarker:                  break;
		case FbxNodeAttribute::eSkeleton:                break;
		case FbxNodeAttribute::eMesh:	  ProcessMesh(fbxNode,out); break;
		case FbxNodeAttribute::eCamera:                  break;
		case FbxNodeAttribute::eLight:                   break;
		case FbxNodeAttribute::eBoundary:                break;
		case FbxNodeAttribute::eOpticalMarker:           break;
		case FbxNodeAttribute::eOpticalReference:        break;
		case FbxNodeAttribute::eCameraSwitcher:          break;
		case FbxNodeAttribute::eNull:                    break;
		case FbxNodeAttribute::ePatch:                   break;
		case FbxNodeAttribute::eNurbs:                   break;
		case FbxNodeAttribute::eNurbsSurface:            break;
		case FbxNodeAttribute::eNurbsCurve:              break;
		case FbxNodeAttribute::eTrimNurbsSurface:        break;
		case FbxNodeAttribute::eUnknown:				 break;
		}
		
	}

	//process children
	for (int i=0;i<fbxNode->GetChildCount();i++)
	{
		WalkHierarchy(fbxNode->GetChild(i));
	}

	void* hFile = CreateFile("test.txt",GENERIC_WRITE ,0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD byteswrite;
	WriteFile(hFile, out.c_str(), out.size(),&byteswrite,NULL);
	FBXSDK_printf("Convert complete!\n");
}

void ProcessMesh( FbxNode* node , std::string& output)
{
	if(node->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
	{
		FbxMesh* pMesh = node->GetMesh();  
		if(pMesh == NULL)  
		{  
			return;  
		}  

		vector<D3DXVECTOR3> m_ObjVerPosArr;
		vector<D3DXVECTOR3> m_ObjVerNorArr;
		vector<D3DXVECTOR2> m_ObjVerUVArr;
		std::string m_ObjVerIndex;

		D3DXVECTOR3 vertex[3];  
		D3DXVECTOR4 color[3];  
		D3DXVECTOR3 normal[3];  
		D3DXVECTOR3 tangent[3];  
		D3DXVECTOR2 uv[3][2];  

		int triangleCount = pMesh->GetPolygonCount();  
		int vertexCounter = 0;  

		int currentPosIndex = -1;
		int currentUVIndex  = -1;
		int currentNorIndex = -1;

		output.append("g submesh1\n");

		for(int i = 0 ; i < triangleCount ; ++i)  
		{  
			m_ObjVerIndex.append("f ");
			for(int j = 0 ; j < 3 ; j++)  
			{  
				int ctrlPointIndex = pMesh->GetPolygonVertex(i , j);  

				// Read the vertex  
				ReadVertex(pMesh , ctrlPointIndex , &vertex[j]);  

				int posFind = VectorFind<D3DXVECTOR3>(m_ObjVerPosArr,vertex[j]);
				if (posFind==-1)
				{
					m_ObjVerPosArr.push_back(vertex[j]);
					currentPosIndex+=1;

					char posIndex[128];
					Format(&posIndex[0],"%d",currentPosIndex+1);
					m_ObjVerIndex.append(posIndex);
					m_ObjVerIndex.append("/");
				}
				else
				{
					char posIndex[128];
					Format(&posIndex[0],"%d",posFind+1);
					m_ObjVerIndex.append(posIndex);
					m_ObjVerIndex.append("/");
				}

				// Read the color of each vertex  
				ReadColor(pMesh , ctrlPointIndex , vertexCounter , &color[j]);  

				// Read the UV of each vertex  
				for(int k = 0 ; k < 1 ; ++k)  
				{  
					ReadUV(pMesh , ctrlPointIndex , pMesh->GetTextureUVIndex(i, j) , k , &(uv[j][k]));  

					int uvFind = VectorFind<D3DXVECTOR2>(m_ObjVerUVArr,uv[j][k]);
					if (uvFind==-1)
					{
						m_ObjVerUVArr.push_back(uv[j][k]);
						currentUVIndex+=1;

						char uvIndex[128];
						Format(&uvIndex[0],"%d",currentUVIndex+1);
						m_ObjVerIndex.append(uvIndex);
						m_ObjVerIndex.append("/");
					}
					else
					{
						char uvIndex[128];
						Format(&uvIndex[0],"%d",uvFind+1);
						m_ObjVerIndex.append(uvIndex);
						m_ObjVerIndex.append("/");
					}
				}  

				// Read the normal of each vertex  
				ReadNormal(pMesh , ctrlPointIndex , vertexCounter , &normal[j]);  
				
				int norFind = VectorFind<D3DXVECTOR3>(m_ObjVerNorArr,normal[j]);
				if (norFind==-1)
				{
					m_ObjVerNorArr.push_back(vertex[j]);
					currentNorIndex+=1;

					char normalIndex[128];
					Format(&normalIndex[0],"%d",currentNorIndex+1);
					m_ObjVerIndex.append(normalIndex);
					m_ObjVerIndex.append(" ");
				}
				else
				{
					char normalIndex[128];
					Format(&normalIndex[0],"%d",norFind+1);
					m_ObjVerIndex.append(normalIndex);
					m_ObjVerIndex.append(" ");
				}
				// Read the tangent of each vertex  
				ReadTangent(pMesh , ctrlPointIndex , vertexCounter , &tangent[j]);  

				vertexCounter++;  
			}  
			m_ObjVerIndex.append("\n");
			// 根据读入的信息组装三角形，并以某种方式使用即可，比如存入到列表中、保存到文件等...  
		} 
		char posIndex[128];

		for (int i = 0 ;i<m_ObjVerPosArr.size() ;i++)
		{
			output.append("v ");
			Format(posIndex,128,"%.6f",m_ObjVerPosArr[i].x);
			output.append(posIndex);
			output.append(" ");
			
			Format(posIndex,128,"%.6f",m_ObjVerPosArr[i].y);
			output.append(posIndex);
			output.append(" ");
			
			Format(posIndex,128,"%.6f",m_ObjVerPosArr[i].z);
			output.append(posIndex);
			
			output.append("\n");
		}

		for (int i = 0 ;i<m_ObjVerUVArr.size() ;i++)
		{
			output.append("vt ");
			Format(posIndex,128,"%.6f",m_ObjVerUVArr[i].x);
			output.append(posIndex);
			output.append(" ");
			Format(posIndex,128,"%.6f",m_ObjVerUVArr[i].y);
			output.append(posIndex);
			output.append("\n");
		}

		for (int i = 0 ;i<m_ObjVerNorArr.size() ;i++)
		{
			output.append("vn ");
			Format(posIndex,128,"%.6f",m_ObjVerNorArr[i].x);
			output.append(posIndex);
			output.append(" ");
			Format(posIndex,128,"%.6f",m_ObjVerNorArr[i].y);
			output.append(posIndex);
			output.append(" ");
			Format(posIndex,128,"%.6f",m_ObjVerNorArr[i].z);
			output.append(posIndex);
			output.append("\n");
		}
		output.append(m_ObjVerIndex);
	}
}

void ReadVertex(FbxMesh* pMesh , int ctrlPointIndex , D3DXVECTOR3* pVertex)  
{  
	FbxVector4* pCtrlPoint = pMesh->GetControlPoints();  

	pVertex->x = pCtrlPoint[ctrlPointIndex][0];  
	pVertex->y = pCtrlPoint[ctrlPointIndex][1];  
	pVertex->z = pCtrlPoint[ctrlPointIndex][2];  
}  

void ReadColor(FbxMesh* pMesh , int ctrlPointIndex , int vertexCounter , D3DXVECTOR4* pColor)  
{  
	if(pMesh->GetElementVertexColorCount() < 1)  
	{  
		return;  
	}  

	FbxGeometryElementVertexColor* pVertexColor = pMesh->GetElementVertexColor(0);  
	switch(pVertexColor->GetMappingMode())  
	{  
	case FbxGeometryElement::eByControlPoint:  
		{  
			switch(pVertexColor->GetReferenceMode())  
			{  
			case FbxGeometryElement::eDirect:  
				{  
					pColor->x = pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mRed;  
					pColor->y = pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mGreen;  
					pColor->z = pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mBlue;  
					pColor->w = pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mAlpha;  
				}  
				break;  

			case FbxGeometryElement::eIndexToDirect:  
				{  
					int id = pVertexColor->GetIndexArray().GetAt(ctrlPointIndex);  
					pColor->x = pVertexColor->GetDirectArray().GetAt(id).mRed;  
					pColor->y = pVertexColor->GetDirectArray().GetAt(id).mGreen;  
					pColor->z = pVertexColor->GetDirectArray().GetAt(id).mBlue;  
					pColor->w = pVertexColor->GetDirectArray().GetAt(id).mAlpha;  
				}  
				break;  

			default:  
				break;  
			}  
		}  
		break;  

	case FbxGeometryElement::eByPolygonVertex:  
		{  
			switch (pVertexColor->GetReferenceMode())  
			{  
			case FbxGeometryElement::eDirect:  
				{  
					pColor->x = pVertexColor->GetDirectArray().GetAt(vertexCounter).mRed;  
					pColor->y = pVertexColor->GetDirectArray().GetAt(vertexCounter).mGreen;  
					pColor->z = pVertexColor->GetDirectArray().GetAt(vertexCounter).mBlue;  
					pColor->w = pVertexColor->GetDirectArray().GetAt(vertexCounter).mAlpha;  
				}  
				break;  
			case FbxGeometryElement::eIndexToDirect:  
				{  
					int id = pVertexColor->GetIndexArray().GetAt(vertexCounter);  
					pColor->x = pVertexColor->GetDirectArray().GetAt(id).mRed;  
					pColor->y = pVertexColor->GetDirectArray().GetAt(id).mGreen;  
					pColor->z = pVertexColor->GetDirectArray().GetAt(id).mBlue;  
					pColor->w = pVertexColor->GetDirectArray().GetAt(id).mAlpha;  
				}  
				break;  
			default:  
				break;  
			}  
		}  
		break;  
	}  
}  

void ReadUV(FbxMesh* pMesh , int ctrlPointIndex , int textureUVIndex , int uvLayer , D3DXVECTOR2* pUV)  
{  
	if(uvLayer >= 2 || pMesh->GetElementUVCount() <= uvLayer)  
	{  
		printf("uv read error\n");
		return ;  
	}  

	FbxGeometryElementUV* pVertexUV = pMesh->GetElementUV(uvLayer);  

	switch(pVertexUV->GetMappingMode())  
	{  
	case FbxGeometryElement::eByControlPoint:  
		{  
			switch(pVertexUV->GetReferenceMode())  
			{  
			case FbxGeometryElement::eDirect:  
				{  
					pUV->x = pVertexUV->GetDirectArray().GetAt(ctrlPointIndex)[0];  
					pUV->y = pVertexUV->GetDirectArray().GetAt(ctrlPointIndex)[1];  
				}  
				break;  

			case FbxGeometryElement::eIndexToDirect:  
				{  
					int id = pVertexUV->GetIndexArray().GetAt(ctrlPointIndex);  
					pUV->x = pVertexUV->GetDirectArray().GetAt(id)[0];  
					pUV->y = pVertexUV->GetDirectArray().GetAt(id)[1];  
				}  
				break;  

			default:  
				break;  
			}  
		}  
		break;  

	case FbxGeometryElement::eByPolygonVertex:  
		{  
			switch (pVertexUV->GetReferenceMode())  
			{  
			case FbxGeometryElement::eDirect:  
			case FbxGeometryElement::eIndexToDirect:  
				{  
					pUV->x = pVertexUV->GetDirectArray().GetAt(textureUVIndex)[0];  
					pUV->y = pVertexUV->GetDirectArray().GetAt(textureUVIndex)[1];  
				}  
				break;  

			default:  
				break;  
			}  
		}  
		break;  
	}  
}  

void ReadNormal(FbxMesh* pMesh , int ctrlPointIndex , int vertexCounter , D3DXVECTOR3* pNormal)  
{  
	if(pMesh->GetElementNormalCount() < 1)  
	{  
		return;  
	}  

	FbxGeometryElementNormal* leNormal = pMesh->GetElementNormal(0);  
	switch(leNormal->GetMappingMode())  
	{  
	case FbxGeometryElement::eByControlPoint:  
		{  
			switch(leNormal->GetReferenceMode())  
			{  
			case FbxGeometryElement::eDirect:  
				{  
					pNormal->x = leNormal->GetDirectArray().GetAt(ctrlPointIndex)[0];  
					pNormal->y = leNormal->GetDirectArray().GetAt(ctrlPointIndex)[1];  
					pNormal->z = leNormal->GetDirectArray().GetAt(ctrlPointIndex)[2];  
				}  
				break;  

			case FbxGeometryElement::eIndexToDirect:  
				{  
					int id = leNormal->GetIndexArray().GetAt(ctrlPointIndex);  
					pNormal->x = leNormal->GetDirectArray().GetAt(id)[0];  
					pNormal->y = leNormal->GetDirectArray().GetAt(id)[1];  
					pNormal->z = leNormal->GetDirectArray().GetAt(id)[2];  
				}  
				break;  

			default:  
				break;  
			}  
		}  
		break;  

	case FbxGeometryElement::eByPolygonVertex:  
		{  
			switch(leNormal->GetReferenceMode())  
			{  
			case FbxGeometryElement::eDirect:  
				{  
					pNormal->x = leNormal->GetDirectArray().GetAt(vertexCounter)[0];  
					pNormal->y = leNormal->GetDirectArray().GetAt(vertexCounter)[1];  
					pNormal->z = leNormal->GetDirectArray().GetAt(vertexCounter)[2];  
				}  
				break;  

			case FbxGeometryElement::eIndexToDirect:  
				{  
					int id = leNormal->GetIndexArray().GetAt(vertexCounter);  
					pNormal->x = leNormal->GetDirectArray().GetAt(id)[0];  
					pNormal->y = leNormal->GetDirectArray().GetAt(id)[1];  
					pNormal->z = leNormal->GetDirectArray().GetAt(id)[2];  
				}  
				break;  

			default:  
				break;  
			}  
		}  
		break;  
	}  
}  

void ReadTangent(FbxMesh* pMesh , int ctrlPointIndex , int vertecCounter , D3DXVECTOR3* pTangent)  
{  
	if(pMesh->GetElementTangentCount() < 1)  
	{  
		return;  
	}  

	FbxGeometryElementTangent* leTangent = pMesh->GetElementTangent(0);  

	switch(leTangent->GetMappingMode())  
	{  
	case FbxGeometryElement::eByControlPoint:  
		{  
			switch(leTangent->GetReferenceMode())  
			{  
			case FbxGeometryElement::eDirect:  
				{  
					pTangent->x = leTangent->GetDirectArray().GetAt(ctrlPointIndex)[0];  
					pTangent->y = leTangent->GetDirectArray().GetAt(ctrlPointIndex)[1];  
					pTangent->z = leTangent->GetDirectArray().GetAt(ctrlPointIndex)[2];  
				}  
				break;  

			case FbxGeometryElement::eIndexToDirect:  
				{  
					int id = leTangent->GetIndexArray().GetAt(ctrlPointIndex);  
					pTangent->x = leTangent->GetDirectArray().GetAt(id)[0];  
					pTangent->y = leTangent->GetDirectArray().GetAt(id)[1];  
					pTangent->z = leTangent->GetDirectArray().GetAt(id)[2];  
				}  
				break;  

			default:  
				break;  
			}  
		}  
		break;  

	case FbxGeometryElement::eByPolygonVertex:  
		{  
			switch(leTangent->GetReferenceMode())  
			{  
			case FbxGeometryElement::eDirect:  
				{  
					pTangent->x = leTangent->GetDirectArray().GetAt(vertecCounter)[0];  
					pTangent->y = leTangent->GetDirectArray().GetAt(vertecCounter)[1];  
					pTangent->z = leTangent->GetDirectArray().GetAt(vertecCounter)[2];  
				}  
				break;  

			case FbxGeometryElement::eIndexToDirect:  
				{  
					int id = leTangent->GetIndexArray().GetAt(vertecCounter);  
					pTangent->x = leTangent->GetDirectArray().GetAt(id)[0];  
					pTangent->y = leTangent->GetDirectArray().GetAt(id)[1];  
					pTangent->z = leTangent->GetDirectArray().GetAt(id)[2];  
				}  
				break;  

			default:  
				break;  
			}  
		}  
		break;  
	}  
}  