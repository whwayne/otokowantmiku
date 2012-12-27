#pragma once
#include "VisCell.h"
#include "OctTree.h"
#include "Renderer.h"
#include "Memory.h"
#include "Frustum.h"
#include "Matrix44.h"
#include <list>

//- this is not a singleton class,because it may be used many times 
class CullSystem
{
public:
	CullSystem();

	virtual ~CullSystem();

	void OnFrame(float deltaTime);

	void Init();

	TreeNode<VisCell>& GetRootNode()
	{
		return m_RootNode; 
	}

	void AttachRenderable(Ptr<Renderable>& renderable);

	void Cull( Frustum& frus, TreeNode<VisCell>& node, std::vector<std::list<Ptr<Renderable>>>& outRenderables);

	void Cull( matrix44& vp, TreeNode<VisCell>& node, std::vector<std::list<Ptr<Renderable>>>& outRenderables);

public:
	void SetDepth(int depth)
	{
		m_Depth = depth;
	}
	void SetCullArea(aabbox& area)
	{
		m_CullArea = area;
	}
protected:	

	void BuildOctTree(TreeNode<VisCell>& node);
	void DestoryOctTree(TreeNode<VisCell>& node);

	TreeNode<VisCell>* OctTreeBoundCheck(TreeNode<VisCell>& node,aabbox& box);

	TreeNode<VisCell> m_RootNode;
	aabbox            m_CullArea;
	int               m_Depth;
protected:	

};