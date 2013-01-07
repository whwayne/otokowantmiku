using System;
using System.Collections.Generic;
using System.Linq;
using ScriptRuntimeLibrary;


namespace UserDefCSharp
{
    public class Move:ScriptEntry
    {
        Actor act = null;

        MeshRenderComponent meshRenderComponent;

        override public void OnFrame()
        {
            if (act == null)
            {
                Util.OutPutToScreenEX();
                act = new Actor();
                meshRenderComponent = new MeshRenderComponent();
                meshRenderComponent.SetMeshID("cup.obj");
                act.AddComponent(meshRenderComponent);

                ActorMgr.AddActor(act);
            }   
        }
    }
}
