#pragma once
//put this in front of <fbxsdk.h> in order to define the macro FBXSDK_NEW_API before <fbxsdk.h>
#include "PreDefined.h"
#include <fbxsdk.h>
#include <d3dx9.h>
#include <string>

void InitializeSdkObjects(FbxManager*& pManager, FbxScene*& pScene);
void DestroySdkObjects(FbxManager* pManager, bool pExitStatus);
void LoadScene(FbxManager* pManager,FbxScene*& pScene, const char* fileName);

void WalkHierarchy(const FbxScene* pScene);
void WalkHierarchy(FbxNode *fbxNode);
void ProcessMesh(FbxNode* node, std::string& output);

void ReadVertex(FbxMesh* pMesh , int ctrlPointIndex , D3DXVECTOR3* pVertex)  ;
void ReadColor(FbxMesh* pMesh , int ctrlPointIndex , int vertexCounter , D3DXVECTOR4* pColor) ; 
void ReadUV(FbxMesh* pMesh , int ctrlPointIndex , int textureUVIndex , int uvLayer , D3DXVECTOR2* pUV) ; 
void ReadNormal(FbxMesh* pMesh , int ctrlPointIndex , int vertexCounter , D3DXVECTOR3* pNormal)  ;
void ReadTangent(FbxMesh* pMesh , int ctrlPointIndex , int vertecCounter , D3DXVECTOR3* pTangent) ; 


