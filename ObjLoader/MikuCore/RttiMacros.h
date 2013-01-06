/*
macroes for classes to use with rtti

edit by zhaoxiaohang 2012.6.23 1.0v
*/

#pragma once
#include "Rtti.h"
#include "Memory.h"
#include "Fcc.h"

#define __DeclareClass(type)\
public:\
static Core::Rtti RTTI;\
void * operator new(size_t size){void *p =  Memory::AllocMemory (Memory::OBJECT, size);return (p);}\
void operator delete(void *p){Memory::FreeMemory(Memory::OBJECT,p);}


#define __DeclareSubClass(type,baseType)\
typedef baseType Super;\
__DeclareClass(type)


#define __ImplementClass(type,fcc,baseType)\
Core::Rtti type::RTTI(Fcc(fcc),#type);
