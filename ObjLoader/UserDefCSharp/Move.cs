using System;
using System.Collections.Generic;
using System.Linq;
using ScriptRuntimeLibrary;


namespace UserDefCSharp
{
    public class Move:ScriptEntry
    {
        override public void OnFrame()
        {
            Util.OutPutToScreenEX();
        }
    }
}
