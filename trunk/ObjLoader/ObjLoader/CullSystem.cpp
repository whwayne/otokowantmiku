#include "CullSystem.h"




CullSystem::CullSystem()
:m_RootNode()
{

}

CullSystem::~CullSystem()
{
	if (m_RootNode.GetChildren().size()==8)
	{
		DestoryOctTree(m_RootNode);
	}
}

void CullSystem::OnFrame( float deltaTime )
{
	
}

void CullSystem::Init()
{
	m_RootNode.SetParent(0);
	m_RootNode.SetDepth(0);
	m_RootNode.GetContent().SetAABB(m_CullArea);
	BuildOctTree(m_RootNode);
}

void CullSystem::DestoryOctTree( TreeNode<VisCell>& node )
{
	if (node.GetChildren().size()==8)
	{
		for( int i = 0 ;i<8; i++ )
		{
			if ( node.GetChildren()[i] )
			{
				DestoryOctTree(*node.GetChildren()[i]);
				o_delete(node.GetChildren()[i]);
			}
		}
	}
}

void CullSystem::BuildOctTree( TreeNode<VisCell>& node )
{
	if (node.GetDepth() == m_Depth )
	{
		return;
	}
	
	node.GetChildren().resize(8);
	for( int i = 0 ;i<8; i++ )
	{
		node.GetChildren()[i] = o_new( TreeNode<VisCell> );
		node.GetChildren()[i]->SetParent( &node );
		node.GetChildren()[i]->SetDepth( node.GetDepth()+1 );
		node.GetChildren()[i]->SetIndex(i);

		VisCell& parentCell = node.GetContent();
		aabbox&   box = parentCell.GetAABB();
		aabbox    baseBox;		
		
		point middle = (box.GetMax()+box.GetMin())*0.5f;
		float xHalf = box.GetMax().X() - middle.X();
		float yHalf	= box.GetMax().Y() - middle.Y();
		float zHalf	= box.GetMax().Z() - middle.Z();

		baseBox.SetMax( box.GetMax() );
		baseBox.SetMin( middle );

		point& pMax = baseBox.GetMax();
		point& pMin = baseBox.GetMin();

		if ( i%2==1 )
		{
			 pMax.X()-=xHalf; 
			 pMin.X()-=xHalf; 
		}
		if ( i>=4 )
		{
			pMax.Y()-=yHalf; 
			pMin.Y()-=yHalf; 

			if (i>=6)
			{
				pMax.Z()-=zHalf; 
				pMin.Z()-=zHalf;
			}
		}
		else if( i>=2 )
		{
			pMax.Z()-=zHalf; 
			pMin.Z()-=zHalf;
		}

		VisCell& childCell = node.GetChildren()[i]->GetContent();
		childCell.SetAABB(baseBox);
		BuildOctTree( *node.GetChildren()[i]);
		
	}
}

void CullSystem::AttachRenderable( Ptr<Renderable>& renderable )
{
	TreeNode<VisCell>* pContentNode = NULL;

	pContentNode = OctTreeBoundCheck( m_RootNode ,renderable->GetWorldBBox() ) ;
	if (pContentNode)
	{
		pContentNode->GetContent().GetRenderables().push_back(renderable);
	}
}

TreeNode<VisCell>* CullSystem::OctTreeBoundCheck( TreeNode<VisCell>& node,aabbox& box )
{
	if (node.GetContent().GetAABB().InterSect(box)==INTERSECTIN)
	{

		if (node.GetChildren().size()==0)
		{
			return &node;
		}
		int inchildc = 0;
		for( int i =0 ; i < 8 ; i++ )
		{
			if (node.GetChildren()[i]->GetContent().GetAABB().InterSect(box)!=INTERSECTIN)
			{
				inchildc++;
			}	
		}
		if (inchildc==8)
		{
			return &node;;
		}
		TreeNode<VisCell>* ret = NULL;
		for( int i =0 ; i < 8 ; i++ )
		{
			 ret = OctTreeBoundCheck(*node.GetChildren()[i],box);
			 if (ret!=NULL)
			 {
				 return ret;
			 }
		}
	}
// 	else
// 	{
// 		if (node.GetParent()  )
// 		{
// 			return OctTreeBoundCheck(*node.GetParent(),box);
// 		}
// 		else
// 		{
// 			return NULL;
// 		}
// 	}
}

void CullSystem::Cull( Frustum& frus, TreeNode<VisCell>& node, std::vector<std::list<Ptr<Renderable>>>& outRenderables)
{
	InterSectResult result = frus.InterSect(node.GetContent().GetAABB());
	if ( !result==INTERSECTOUT )
	{
		std::list<Ptr<Renderable>>::iterator iter = node.GetContent().GetRenderables().begin();
		if (result== INTERSECTIN)
		{
			for (;iter!=node.GetContent().GetRenderables().end();iter++)
			{
				RenderType rType = (*iter)->GetRenderType();
				outRenderables[rType].push_back((*iter));
			}
		}
		else
		{
			for (;iter!=node.GetContent().GetRenderables().end();iter++)
			{
				if ( frus.InterSect((*iter)->GetSubMesh()->GetVertexBuffer()->GetBBox())!= INTERSECTOUT)
				{
					RenderType rType = (*iter)->GetRenderType();
					outRenderables[rType].push_back((*iter));
				}
			}
		}
		for (int i = 0 ;i<(int)node.GetChildren().size();i++)
		{
			Cull( frus,*node.GetChildren()[i],outRenderables );
		}
		
	}
	
}

void CullSystem::Cull( matrix44& vp, TreeNode<VisCell>& node, std::vector<std::list<Ptr<Renderable>>>& outRenderables )
{
	InterSectResult result = node.GetContent().GetAABB().InterSect(vp);
	if ( !result==INTERSECTOUT )
	{
		std::list<Ptr<Renderable>>::iterator iter = node.GetContent().GetRenderables().begin();
		if (result== INTERSECTIN)
		{
			for (;iter!=node.GetContent().GetRenderables().end();iter++)
			{
				RenderType rType = (*iter)->GetRenderType();
				outRenderables[rType].push_back((*iter));
			}
		}
		else
		{
			for (;iter!=node.GetContent().GetRenderables().end();iter++)
			{
				if ( (*iter)->GetWorldBBox().InterSect(vp)!= INTERSECTOUT)
				{
					RenderType rType = (*iter)->GetRenderType();
					outRenderables[rType].push_back((*iter));
				}
			}
		}
		for (int i = 0 ;i<(int)node.GetChildren().size();i++)
		{
			Cull( vp,*node.GetChildren()[i],outRenderables );
		}

	}
}

