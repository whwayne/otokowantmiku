using System;

using System.Runtime.CompilerServices;

namespace ScriptRuntimeLibrary
{
    public static class Util
    {

        static void PrintIntf(int num)
        {

        }
        public static void OutPutToScreenEX()
        {
            OutPutToScreen();
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void OutPutToScreen();
    }

}
