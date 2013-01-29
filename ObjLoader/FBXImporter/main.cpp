#pragma once
//put this in front of <fbxsdk.h> in order to define the macro FBXSDK_NEW_API before <fbxsdk.h>
#include "PreDefined.h" 
#include <fbxsdk.h>
#ifdef FBXSDK_ENV_WIN 
// On Windows platform need to include this to define  _msize()
#include <malloc.h>
#endif

#include <string>
#include <stdio.h>
#include <conio.h>
#include "FbxCommon.h"

int main()
{

	FbxManager* lSdkManager = NULL;
	FbxScene* lScene = NULL;
	bool lResult;
	// Prepare the FBX SDK.
	InitializeSdkObjects(lSdkManager, lScene);

	char szInput[1024];
	while (1)
	{	
		
		scanf("%s", szInput);
		LoadScene(lSdkManager,lScene,szInput);
		WalkHierarchy(lScene);
		lScene = NULL;
	}

	return 0;
}