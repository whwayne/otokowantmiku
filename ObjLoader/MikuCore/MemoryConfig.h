#pragma once
#include <Windows.h>
#include "Interlocked.h"

#define MIKU_MEMORY_STATS
#define HEAP_LFH 2

namespace Memory
{
	static const int m = 1024;

	enum HeapType
	{
		OBJECT = 0,
		STRING,
		HEAPCOUNT,
	};

#ifdef MIKU_MEMORY_STATS
	extern int volatile TotalAllocCount;
	extern int volatile TotalAllocSize;
	extern int volatile HeapTypeAllocCount[HEAPCOUNT];
	extern int volatile HeapTypeAllocSize[HEAPCOUNT];
#endif

	static void* HeapHandles[HEAPCOUNT];

	
	void SetUpHeaps();

	void DestoryHeaps();

	void* AllocMemory(HeapType type,size_t size);

	void FreeMemory(HeapType type,void* ptr);


	__forceinline unsigned char* PtrAlign16AndWriteMask(unsigned char* ptr)
	{
		unsigned char Mask = (unsigned char)((DWORD)ptr&15);
		ptr = (unsigned char*)((DWORD)(ptr+16)&~15);
		ptr[-1] = Mask;
		
		return ptr;
	}
	
	__forceinline unsigned char* PtrUnalign16(unsigned char* ptr)
	{
		ptr = (unsigned char*)( (((unsigned int)ptr)|(unsigned int) ptr[-1]) -16);
		return ptr;
	}
	
}
