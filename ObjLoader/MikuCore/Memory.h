#pragma once
#include <Windows.h>


#define o_new(T) new T()

#define o_new2(T,N) new T##N()

#define o_delete(T) delete T

#define o_newArray(T,COUNT) new T[COUNT]()

#define o_deleteArray(T) delete[] T