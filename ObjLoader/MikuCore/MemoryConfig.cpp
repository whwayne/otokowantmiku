#include "MemoryConfig.h"



namespace Memory
{

#ifdef MIKU_MEMORY_STATS
	int volatile TotalAllocCount;
	int volatile TotalAllocSize;
	int volatile HeapTypeAllocCount[HEAPCOUNT];
	int volatile HeapTypeAllocSize[HEAPCOUNT];
#endif

	void SetUpHeaps()
	{
		for (int i = 0;i<HEAPCOUNT;i++)
		{
			HeapHandles[i] = HeapCreate(0,4*m*m,0);


			ULONG HeapInformation = HEAP_LFH;
			HeapSetInformation(HeapHandles[i],HeapCompatibilityInformation,&HeapInformation,sizeof(HeapInformation));
			//lfh is auto created in windows version above vista,so I write down this fucking code to show that ,I know what lfh is!
		}
	}

	void DestoryHeaps()
	{
		for (int i = 0;i<HEAPCOUNT;i++)
		{
			HeapDestroy(HeapHandles[i]);
		}
	}

	void* AllocMemory( HeapType type ,size_t size)
	{

		void* ptr = HeapAlloc(HeapHandles[type],0 ,size+16);

#ifdef MIKU_MEMORY_STATS
		SIZE_T s = HeapSize(HeapHandles[type], 0, ptr);
		Interlocked::Increment(TotalAllocCount);
		Interlocked::Add(TotalAllocSize, int(s));
		Interlocked::Increment(HeapTypeAllocCount[type]);
		Interlocked::Add(HeapTypeAllocSize[type], int(s));
#endif

		return (void*)PtrAlign16AndWriteMask((unsigned char*)ptr);
	}

	void FreeMemory( HeapType type,void* ptr )
	{
		void* fptr = (void*)PtrUnalign16((unsigned char*)ptr);

#ifdef MIKU_MEMORY_STATS
		size_t size = HeapSize(HeapHandles[type], 0, fptr);
#endif

		HeapFree(HeapHandles[type],0, fptr);

#ifdef MIKU_MEMORY_STATS
		Interlocked::Add(TotalAllocSize, -int(size));
		Interlocked::Decrement(TotalAllocCount);
		Interlocked::Add(HeapTypeAllocSize[type], -int(size));
		Interlocked::Decrement(HeapTypeAllocCount[type]);
#endif
	}

}