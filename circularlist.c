#include <stdio.h>
#include <stdlib.h>
#include "circularlist.h"

LinkedList* createCLList()
{
	LinkedList	*new;

	new = malloc(sizeof(LinkedList));
	if (new == NULL)
	{
		printf("createCLList() : malloc failed\n");
		return (NULL);
	}
	new->currentElementCount = 0;
	new->tail = NULL;
	return (new);
}

int	addCLElement(LinkedList* pList, int position, ListNode element)
{
	ListNode	*curr;
	ListNode	*newNode;

	if (pList == NULL || position < 0 || position > pList->currentElementCount)
	{
		printf("addCLElement() : invalid argument\n");
		return (FALSE);
	}
	newNode = malloc(sizeof(ListNode));
	if(newNode == NULL)
	{
		printf("addCLElement() : malloc filaed\n");
		return (FALSE);
	}
	newNode->data = element.data;
	newNode->pLink = NULL;
	if (pList->tail == NULL)
	{
		newNode->pLink = newNode;
		pList->tail = newNode;
	}
	else
	{
		if (position == 0)
			curr = pList->tail;
		else
			curr = getCLElement(pList, position - 1);
		newNode->pLink = curr->pLink;
		curr->pLink = newNode;
	}
	pList->currentElementCount++;
	return (TRUE);
}

int	addCLElementBack(LinkedList* pList, ListNode element)
{
	addCLElement(pList, 0, element);
	pList->tail = pList->tail->pLink;
	return (TRUE);
}

int removeCLElement(LinkedList* pList, int position)
{
	ListNode	*curr;
	ListNode	*toDelete;

	if(pList == NULL || position < 0)
	{
		printf("removeCLElement() : invaild argument\n");
		return (FALSE);
	}
	if (position == 0)
		curr = pList->tail;
	else
		curr = getCLElement(pList, position - 1);
	toDelete = curr->pLink;
	curr->pLink = toDelete->pLink;
	if(pList->tail == toDelete)
	{
		if (pList->tail->pLink == pList->tail)
			pList->tail = NULL;
		else
			pList->tail = curr;
	}
	free(toDelete);
	pList->currentElementCount--;
	return (TRUE);
}

ListNode* getCLElement(LinkedList* pList, int position)
{
	ListNode	*curr;

	if(pList == NULL || position < 0 || position >= pList->currentElementCount)
	{
		printf("getCLElement() : invalid argument\n");
		return (NULL);
	}
	if (position == pList->currentElementCount - 1)
		return (pList->tail);
	curr = pList->tail->pLink;
	while (position > 0)
	{
		curr = curr->pLink;
		position--;
	}
	return (curr);
}

void clearCLList(LinkedList* pList)
{
	if (pList == NULL)
	{
		printf("clearCLList() : invalide argument\n");
		return ;
	}
	while (pList->tail != NULL)
		removeCLElement(pList, 0);
}

int getCLListLength(LinkedList* pList)
{
	if (pList == NULL)
	{
		printf("getCLListLength() : invalide argument\n");
		return (-1);
	}
	return (pList->currentElementCount);
}

void deleteCLList(LinkedList* pList)
{
	if (pList == NULL)
		return ;
	clearCLList(pList);
	free(pList);
}

void	displayCircularList(LinkedList *pList)
{
	int			iValue;
	int			iIndex;
	int			count;
	const int	NUMBERS_PER_LINE = 5;
	ListNode	*curr;

	if (pList == NULL ) 
	{
		printf("displayCircularList() : invalid argument\n");
		return ;
	}
	if(pList->tail == NULL)
		return ;
	curr = pList->tail->pLink;
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
