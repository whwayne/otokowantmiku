#pragma once
#include <vector>
#include <assert.h>
#include <math.h>
#include "Memory.h"

template<typename NodeContent>
class TreeNode
{
public:
	TreeNode();
	virtual ~TreeNode();

	std::vector<TreeNode<NodeContent>*>& GetChildren();
	TreeNode<NodeContent>* GetParent() const;
	void SetParent(TreeNode<NodeContent>* node);
	void SetDepth(int d);
	int  GetDepth();
	void SetIndex(int i);
	int  GetIndex();
	NodeContent& GetContent() ;
	void SetContent(NodeContent& content);
protected:
	std::vector< TreeNode<NodeContent>* > mpChildren;
	TreeNode<NodeContent>* mpParent;
	int mDepth;//start width 1
	int mIndex;// start width 0
	NodeContent mContent;
private:

};

template<typename NodeContent>
void TreeNode<NodeContent>::SetContent( NodeContent& content)
{
	mContent = content;
}

template<typename NodeContent>
NodeContent& TreeNode<NodeContent>::GetContent() 
{
	return mContent;
}

template<typename NodeContent>
int TreeNode<NodeContent>::GetIndex()
{
	return mIndex;
}

template<typename NodeContent>
void TreeNode<NodeContent>::SetIndex( int i )
{
	mIndex = i;
}

template<typename NodeContent>
int TreeNode<NodeContent>::GetDepth()
{
	return mDepth;
}

template<typename NodeContent>
void TreeNode<NodeContent>::SetDepth( int d )
{
	mDepth = d;
}

template<typename NodeContent>
void TreeNode<NodeContent>::SetParent( TreeNode<NodeContent>* node )
{
	mpParent = node;
}

template<typename NodeContent>
TreeNode<NodeContent>* TreeNode<NodeContent>::GetParent() const
{
	return mpParent;
}

template<typename NodeContent>
TreeNode<NodeContent>::TreeNode()
	:mpParent(0)
	,mpChildren()
{
	
}


template<typename NodeContent>
TreeNode<NodeContent>::~TreeNode()
{

}

template<typename NodeContent>
std::vector<TreeNode<NodeContent>*>& TreeNode<NodeContent>::GetChildren()
{
	return mpChildren;
}

//----------------------upper is the nodes, below will be the oct tree that the memory is in one block---------------------------
template<typename NodeContent>
class OctTreeV
{
public:
	OctTreeV();
	OctTreeV(int depth);
	virtual ~OctTreeV();
	
	std::vector<TreeNode<NodeContent>>& GetAllContents();
	
	
protected:
	int GetAllContentCount();
	int GetStartIndexByDepth(int depth);
	int GetChildStartIndex(TreeNode<NodeContent>& node);
	void BuildRecruse(TreeNode<NodeContent>& node);

protected:
	int mDepth;
	std::vector<TreeNode<NodeContent>> mAllContents;

	TreeNode<NodeContent>* pHead;
private:
};


template<typename NodeContent>
OctTreeV<NodeContent>::OctTreeV()
	:mDepth(0)
	,mAllContents()
	,pHead(0)
{
	
}

template<typename NodeContent>
OctTreeV<NodeContent>::OctTreeV( int depth )
	:mDepth(depth)
	,mAllContents()
	,pHead()
{
	mAllContents.resize( GetAllContentCount());
	pHead = o_new(TreeNode<NodeContent>);
	pHead->SetIndex(0);
	pHead->SetDepth(0);
	pHead->SetParent(NULL);
    BuildRecruse(*pHead);	
}

template<typename NodeContent>
OctTreeV<NodeContent>::~OctTreeV()
{

}
template<typename NodeContent>
int OctTreeV<NodeContent>::GetAllContentCount()
{
	int count = 0;
	for (int i = 0;i<mDepth;i++)
	{
		count+=(int) pow((float)8,i);
	}
	return count;

}

template<typename NodeContent>
int OctTreeV<NodeContent>::GetStartIndexByDepth( int depth )
{
	int count = 0;
	for (int i = 0;i<depth;i++)
	{
		count+=(int) pow((float)8,i);
	}
	return count;
}

template<typename NodeContent>
int OctTreeV<NodeContent>::GetChildStartIndex( TreeNode<NodeContent>& node )
{
	int count = 0;
	for (int i = 0;i<node.GetDepth();i++)
	{
		count+=(int) pow((float)8,i);
	}

	TreeNode<NodeContent>* pParent = node.GetParent();
	while()
	{
		
	}
	return count;
}

template<typename NodeContent>
void OctTreeV<NodeContent>::BuildRecruse(TreeNode<NodeContent>& node)
{
	for (int i = 0;i<8;i++)
	{
		node.GetChildren()[i] = o_new(TreeNode<NodeContent>);
		node.GetChildren()[i]->SetParent(&node);
		node.GetChildren()[i]->SetDepth(node.GetDepth()+1);
		node.GetChildren()[i]->SetIndex(i);

		BuildRecruse(*node.GetChildren()[i]);
	}
}

template<typename NodeContent>
std::vector<TreeNode<NodeContent>>& OctTreeV<NodeContent>::GetAllContents()
{
	return mAllContents;
}
