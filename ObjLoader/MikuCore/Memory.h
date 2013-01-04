#pragma once
#include "MemoryConfig.h"
#include <exception>

namespace Memory
{

}

#ifdef new
#undef new
#endif

#ifdef delete
#undef delete
#endif
//------------------------------------------------------------------------------
/**
    Replacement global new operator.
*/
__forceinline void*
__CRTDECL operator new(size_t size)
{
    return Memory::AllocMemory (Memory::OBJECT, size);
}

//------------------------------------------------------------------------------
/**
    Replacement global new[] operator.
*/
__forceinline void*
__CRTDECL operator new[](size_t size)
{
	return Memory::AllocMemory (Memory::OBJECT, size);
}

//------------------------------------------------------------------------------
/**
    Replacement global delete operator.
*/
__forceinline void
__CRTDECL operator delete(void* p)
{
    Memory::FreeMemory(Memory::OBJECT, p);
}

//------------------------------------------------------------------------------
/**
    Replacement global delete[] operator.
*/
__forceinline void
__CRTDECL operator delete[](void* p)
{
    Memory::FreeMemory(Memory::OBJECT, p);
}



#define o_new(T) new T

#define o_new2(T,N) new T##N()

#define o_delete(T) delete T 

#define o_newArray(T,COUNT) new T[COUNT]()

#define o_deleteArray(T) delete[] T