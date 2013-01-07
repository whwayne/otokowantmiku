using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace ScriptRuntimeLibrary
{
    public class Actor:Base
    {
        public Actor()
        {
            ICall_Actor_Bind(this);
        }
        private Actor(__DummyClass cl)
        {
            cl = null;
        }

        public void AddComponent(Component com)
        {
            ICall_Actor_AddComponent(this,com);
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void ICall_Actor_Bind(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void ICall_Actor_AddComponent(Actor self, Component com);
    }
}
