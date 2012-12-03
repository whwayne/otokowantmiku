#pragma once
#include <string>
#include <Windows.h>
#include "Res.h"
#include "Event.h"
//------------------------------------------------------------------------------
/**
    @class Win360::Win360Thread
    
    Win32/Xbox360 implementation of thread class.
    
    (C) 2006 Radon Labs GmbH
*/

// zhao hang did the 2nd edit
//------------------------------------------------------------------------------

class Thread : public	Res
{
    
public:
    /// thread priorities
    enum Priority
    {
        Low,
        Normal,
        High,
    };

    /// constructor
    Thread();
    /// destructor
    virtual ~Thread();
    /// set the thread priority
    void SetPriority(Priority p);
    /// get the thread priority
    Priority GetPriority() const;
//     /// set cpu core on which the thread should be running
//     void SetCoreId(System::Cpu::CoreId coreId);
//     /// get the cpu core on which the thread should be running
//     System::Cpu::CoreId GetCoreId() const;
    /// set stack size in bytes (default is 4 KByte)
    void SetStackSize(int s);
    /// get stack size
    int GetStackSize() const;
    /// set thread name
    void SetName(const std::string& n);
    /// get thread name
    const std::string& GetName() const;
    /// start executing the thread code, returns when thread has actually started
    void Start();
    /// request threading code to stop, returns when thread has actually finished
    void Stop();
    /// return true if thread has been started
    bool IsRunning() const;
    
    /// set thread name from within thread context
  //  static void SetMyThreadName(const char* n);
    /// obtain name of thread from within thread context
  //  static const char* GetMyThreadName();
    /// get the thread ID of this thread (0 == MainThread)
  //  static Threading::ThreadId GetMyThreadId();
    
   
protected:
    /// override this method if your thread loop needs a wakeup call before stopping
    virtual void EmitWakeupSignal();
    /// this method runs in the thread context
    virtual void DoWork();
    /// check if stop is requested, call from DoWork() to see if the thread proc should quit
    bool ThreadStopRequested() const;

private:
    /// internal thread proc helper function
    static DWORD WINAPI ThreadProc(LPVOID self);

    HANDLE threadHandle;
    Event threadStartedEvent;
    Event stopRequestEvent;
    bool running;
    Priority priority;
    int stackSize;
    std::string name;
//     System::Cpu::CoreId coreId;
//     ThreadLocal static const char* ThreadName;

};

//------------------------------------------------------------------------------
/**
*/
inline bool
Thread::IsRunning() const
{
    return (0 != this->threadHandle);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Thread::SetPriority(Priority p)
{
    this->priority = p;
}

//------------------------------------------------------------------------------
/**
*/
inline Thread::Priority
Thread::GetPriority() const
{
    return this->priority;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Thread::SetStackSize(int s)
{
    this->stackSize = s;
}

//------------------------------------------------------------------------------
/**
*/
inline int
Thread::GetStackSize() const
{
    return this->stackSize;
}

//------------------------------------------------------------------------------
/**
    If the derived DoWork() method is running in a loop it must regularly
    check if the process wants the thread to terminate by calling
    ThreadStopRequested() and simply return if the result is true. This
    will cause the thread to shut down.
*/
inline bool
Thread::ThreadStopRequested() const
{
    return this->stopRequestEvent.Peek();
}

//------------------------------------------------------------------------------
/**
    Set the thread's name. To obtain the current thread's name from anywhere
    in the thread's execution context, call the static method
    Thread::GetMyThreadName().
*/
inline void
Thread::SetName(const std::string& n)
{
  
    this->name = n;
}

//------------------------------------------------------------------------------
/**
    Get the thread's name. This is the vanilla method which
    returns the name member. To obtain the current thread's name from anywhere
    in the thread's execution context, call the static method
    Thread::GetMyThreadName().
*/
inline const std::string&
Thread::GetName() const
{
    return this->name;
}

//------------------------------------------------------------------------------
/**
*/
// inline void
// Win360Thread::SetCoreId(System::Cpu::CoreId id)
// {
//     this->coreId = id;
// }
// 
// //------------------------------------------------------------------------------
// /**
// */
// inline System::Cpu::CoreId
// Win360Thread::GetCoreId() const
// {
//     return this->coreId;
// }

//------------------------------------------------------------------------------

