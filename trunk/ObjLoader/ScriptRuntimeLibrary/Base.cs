using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace ScriptRuntimeLibrary
{
    [StructLayout(LayoutKind.Sequential)] 
    public class Base
    {
        public Base()
        {

        }

        private IntPtr CppObjectPtr;
    }
}
