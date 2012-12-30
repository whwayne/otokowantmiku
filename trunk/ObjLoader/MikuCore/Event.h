#pragma once
//------------------------------------------------------------------------------
/**
    @class Win360::Win360Event

    Win32/Xbox360 implmentation of an event synchronization object.

    (C) 2006 Radon Labs GmbH
	// zhao hang did the 2nd edit
*/
#include <Windows.h>
#include <assert.h>

//------------------------------------------------------------------------------

class Event
{
public:
    /// constructor
    Event();
    /// destructor
    ~Event();
    /// signal the event
    void Signal();
    /// wait for the event to become signalled
    void Wait() const;
    /// wait for the event with timeout in millisecs
    bool WaitTimeout(int ms) const;
    /// check if event is signalled
    bool Peek() const;
private:
    HANDLE event;
};

//------------------------------------------------------------------------------
/**
*/
inline
Event::Event()
{
    this->event = CreateEvent(NULL, FALSE, FALSE, NULL);
    assert(0 != this->event);
}

//------------------------------------------------------------------------------
/**
*/
inline
Event::~Event()
{
    assert(0 != this->event);
    CloseHandle(this->event);
    this->event = 0;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Event::Signal()
{
    assert(0 != this->event);
    SetEvent(this->event);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Event::Wait() const
{
    assert(0 != this->event);
    WaitForSingleObject(this->event, INFINITE);
}

//------------------------------------------------------------------------------
/**
    Waits for the event to become signaled with a specified timeout
    in milli seconds. If the method times out it will return false,
    if the event becomes signalled within the timeout it will return 
    true.
*/
inline bool
Event::WaitTimeout(int timeoutInMilliSec) const
{
    assert(0 != this->event);
    DWORD res = WaitForSingleObject(this->event, timeoutInMilliSec);
    return (WAIT_TIMEOUT == res) ? false : true;
}

//------------------------------------------------------------------------------
/**
    This checks if the event is signalled and returnes immediately.
*/
inline bool
Event::Peek() const
{
    
    DWORD res = WaitForSingleObject(this->event, 0);
    return (WAIT_TIMEOUT == res) ? false : true;
}

//------------------------------------------------------------------------------


