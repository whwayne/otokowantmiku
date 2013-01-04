#pragma once

#include <Windows.h>
//------------------------------------------------------------------------------

class Interlocked
{
public:
    /// interlocked increment
    static int Increment(int volatile& var);
    /// interlocked decrement
    static int Decrement(int volatile& var);
    /// interlocked add
    static void Add(int volatile& var, int add);
};

//------------------------------------------------------------------------------
/**
*/
inline int
Interlocked::Increment(int volatile& var)
{
    return InterlockedIncrement((volatile LONG*)&var);
}

//------------------------------------------------------------------------------
/**
*/
inline int
Interlocked::Decrement(int volatile& var)
{
    return InterlockedDecrement((volatile LONG*)&var);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Interlocked::Add(int volatile& var, int add)
{
    InterlockedExchangeAdd((volatile LONG*)&var, add);
}
//------------------------------------------------------------------------------
