using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace ScriptRuntimeLibrary
{
    public static class ActorMgr
    {
        public static void AddActor(Actor act)
        {
            ICall_ActorMgr_AddActor(act);
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void ICall_ActorMgr_AddActor(Actor act);
    }
}
