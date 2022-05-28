#include <stdio.h>
#include <stdlib.h>
#include "bintraversal.h"

static void	preorderTraversal(BinTreeNode *pNode)
{
	if (pNode == NULL)
		return ;
	printf("%d ", pNode->data);
	pNode->visited = TRUE;
	preorderTraversal(getLeftChildNodeBT(pNode));
	preorderTraversal(getRightChildNodeBT(pNode));
}

void	preorderTraversalBinTree(BinTree *pBinTree)
{
	BinTreeNode	*root;

	if (pBinTree == NULL)
		return ;
	root = getRootNodeBT(pBinTree);
	preorderTraversal(root);	
}

static void	inorderTraversal(BinTreeNode *pNode)
{
	if (pNode == NULL)
		return ;
	inorderTraversal(getLeftChildNodeBT(pNode));
	printf("%d ", pNode->data);
	pNode->visited = TRUE;
	inorderTraversal(getRightChildNodeBT(pNode));
}

void	inorderTraversalBinTree(BinTree *pBinTree)
{
	BinTreeNode	*root;

	if (pBinTree == NULL)
		return ;
	root = getRootNodeBT(pBinTree);
	inorderTraversal(root);
}

static void	postorderTraversal(BinTreeNode *pNode)
{
	if (pNode == NULL)
		return ;
	postorderTraversal(getLeftChildNodeBT(pNode));
	postorderTraversal(getRightChildNodeBT(pNode));
	printf("%d ", pNode->data);
	pNode->visited = TRUE;
}

void	postorderTraversalBinTree(BinTree *pBinTree)
{
	BinTreeNode	*root;

	if (pBinTree == NULL)
		return ;
	root = getRootNodeBT(pBinTree);
	postorderTraversal(root);
}
