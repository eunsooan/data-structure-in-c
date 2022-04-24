#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

LinkedList	*createLinkedList()
{
	LinkedList	*newList;

	newList = malloc(sizeof(LinkedList));
	if (newList == NULL)
    {
        printf("createLinkedList(): malloc failed\n");
		return (NULL);
    }
	newList->currentElementCount = 0;
	newList->headerNode.pLink = NULL;
	return (newList);
}

int	addLLElement(LinkedList *pList, int position, ListNode element)
{
	ListNode    *prev;
	ListNode	*newNode;

	if (pList == NULL
        || position < 0
        || position > pList->currentElementCount)
    {
        printf("addLLElement(): invalid argument\n");
		return (FALSE);
    }
    prev = getLLElement(pList, position - 1);
	newNode = malloc(sizeof(ListNode));
	if (newNode == NULL)
    {
        printf("addLLElement(): malloc failed\n");
		return (FALSE);
    }
	newNode->data = element.data;
	newNode->pLink = prev->pLink;
	prev->pLink = newNode;
	pList->currentElementCount++;
	return (TRUE);
}

int	removeLLElement(LinkedList *pList, int position)
{
	ListNode	*prev;
	ListNode	*delNode;

	if (pList == NULL
        || position < 0
        || position >= pList->currentElementCount)
    {
        printf("removeLLElement(): invalid argument\n");
		return (FALSE);
    }
    prev = getLLElement(pList, position - 1);
    delNode = prev->pLink;
    prev->pLink = prev->pLink->pLink;
    free(delNode);
	pList->currentElementCount--;
	return (TRUE);
}

ListNode	*getLLElement(LinkedList *pList, int position)
{
	ListNode	*curr;

	if (pList == NULL
        || position < 0
        || position >= pList->currentElementCount)
    {
        printf("getLLElement(): invalid argument\n");
		return (NULL);
    }
	curr = pList->headerNode.pLink;
	while (position > 0)
	{
		curr = curr->pLink;
		position--;
	}
	return (curr);
}

void	displayLinkedList(LinkedList *pList)
{
	const int	NUMBERS_PER_LINE = 5;
	int			iValue;
	int			iIndex;
	int			count;
	ListNode	*curr;

	curr = pList->headerNode.pLink;
	iValue = 0;
	iIndex = 0;
	while (iValue < pList->currentElementCount)
	{
		printf(" %9d |", curr->data);
		if(iValue % NUMBERS_PER_LINE == NUMBERS_PER_LINE - 1
			|| iValue + 1 == pList->currentElementCount)
		{
			count = iValue - iIndex + 1;
			printf("\n");
			while (iValue >= iIndex)
			{
				printf(" %9d |", iIndex);
				iIndex++;
			}
			printf("\n");
			while (count > 0)
			{
				printf("------------");
				count--;
			}
			printf("\n");
		}
		curr = curr->pLink;
		iValue++;
	}
}

void	clearLinkedList(LinkedList *pList)
{
	ListNode	*delNode;

    if (pList == NULL)
    {
        printf("clearLinkedList(): invalid argument\n");
        return ;
    }
	while (pList->headerNode.pLink != NULL)
	{
		delNode = pList->headerNode.pLink;
		pList->headerNode.pLink = delNode->pLink;
		free(delNode);
	}
	pList->currentElementCount = 0;
}
	
int	getLinkedListLength(LinkedList *pList)
{
    if (pList == NULL)
    {
        printf("getLinkedListLength(): invalid argument\n");
        return (-1);
    }
	return (pList->currentElementCount);
}

void	deleteLinkedList(LinkedList **pList)
{
    if (pList == NULL || *pList == NULL)
    {
        printf("deleteLinkedList(): invalid argument\n");
        return ;
    }
	clearLinkedList(*pList);
	free(*pList);
	*pList = NULL;
}
