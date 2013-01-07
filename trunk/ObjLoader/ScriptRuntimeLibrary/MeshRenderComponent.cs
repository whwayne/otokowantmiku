using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace ScriptRuntimeLibrary
{
    public class MeshRenderComponent:Component
    {
        public MeshRenderComponent()
        {
            ICall_MeshRenderComponent_Bind(this);
        }
        private MeshRenderComponent(__DummyClass cl)
        {
            cl = null;
        }

        public void SetMeshID(string id)
        {
            ICall_MeshRenderComponent_SetMeshID(this, id);
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void ICall_MeshRenderComponent_Bind(MeshRenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern static void ICall_MeshRenderComponent_SetMeshID(MeshRenderComponent self,string id);

        
    }
}
