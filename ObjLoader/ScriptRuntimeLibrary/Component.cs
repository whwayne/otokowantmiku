using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ScriptRuntimeLibrary
{
    public class Component:Base
    {
        public Component()
        {

        }
        private Component(__DummyClass cl)
        {
            cl = null;
        }
    }
}
