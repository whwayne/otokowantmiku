#pragma once
//------------------------------------------------------------------------------
/**
    @class Win360::Win360CriticalSection
  
    Win32/Xbox360-implementation of critical section. Critical section
    objects are used to protect a portion of code from parallel
    execution. Define a static critical section object and
    use its Enter() and Leave() methods to protect critical sections
    of your code.
    
    (C) 2006 Radon Labs GmbH
	// zhao hang did the 2nd edit
*/
#include <Windows.h>

//------------------------------------------------------------------------------

class CriticalSection
{
public:
    /// constructor
    CriticalSection();
    /// destructor
    ~CriticalSection();
    /// enter the critical section
    void Enter() const;
    /// leave the critical section
    void Leave() const;
private:
    CRITICAL_SECTION criticalSection;
};

//------------------------------------------------------------------------------
/**
*/
inline
CriticalSection::CriticalSection()
{
    InitializeCriticalSectionAndSpinCount(&this->criticalSection, 1024);
}

//------------------------------------------------------------------------------
/**
*/
inline
CriticalSection::~CriticalSection()
{
    DeleteCriticalSection(&this->criticalSection);
}

//------------------------------------------------------------------------------
/**
*/
inline void
CriticalSection::Enter() const
{
    EnterCriticalSection(const_cast<LPCRITICAL_SECTION>(&this->criticalSection));
}

//------------------------------------------------------------------------------
/**
*/
inline void
CriticalSection::Leave() const
{
    LeaveCriticalSection(const_cast<LPCRITICAL_SECTION>(&this->criticalSection));
}


//------------------------------------------------------------------------------
