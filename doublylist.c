#include"doublylist.h"
#include<stdio.h>
#include<stdlib.h>

DoublyList	*createDoublyList()
{
	DoublyList *dList;

	dList = malloc(sizeof(DoublyList));
	if(dList == NULL)
	{
		printf("createDoublyList() : malloc failed\n");
		return (NULL);
	}
	dList->currentElementCount = 0;
	dList->headerNode.pLLink = NULL;
	dList->headerNode.pRLink = NULL;
	return (dList);
}

void deleteDoublyList(DoublyList* pList)
{
	if (pList == NULL)
	{
		printf("deleteDoublyList() : invalid argument\n");
		return ;
	}
	clearDoublyList(pList);
	free(pList);
}

int	addDLElement(DoublyList *pList, int position, DoublyListNode element)
{
	DoublyListNode	*curr;
	DoublyListNode	*new;

	if(position > pList->currentElementCount || position < 0 
		|| pList == NULL)
	{
		printf("addDLElement() : invalid argument\n");
		return (FALSE);
	}
	new = malloc(sizeof(DoublyListNode));
	if(new == NULL)
	{
		printf("addDLElement() : malloc failed\n");
		return (FALSE);
	}
	*new = element;
	curr = &pList->headerNode;
	while(position > 0)
	{
		curr = curr->pRLink;
		position--;
	}
	new->pRLink = curr->pRLink;
	new->pLLink = curr;
	if(new->pRLink != NULL)
		new->pRLink->pLLink = new;
	curr->pRLink = new;
	pList->currentElementCount++;
	return (TRUE);
}

int	removeDLElement(DoublyList *pList, int position)
{
	DoublyListNode	*curr;
	DoublyListNode	*toDelete;

	if (pList->currentElementCount == 0)
		return (FALSE);
	if(pList == NULL || position >= pList->currentElementCount || position < 0)
	{
		printf("removeDLElement() : invalid argument\n");
		return (FALSE);
	}
	curr = &pList->headerNode;
	while(position > 0)
	{
		curr = curr->pRLink;
		position--;
	}
	toDelete = curr->pRLink;
	curr->pRLink = toDelete->pRLink;
	if(toDelete->pRLink != NULL)
		toDelete->pRLink->pLLink = curr;
	free(toDelete);
	pList->currentElementCount--;
	return(TRUE);
}

void	clearDoublyList(DoublyList *pList)
{
	if (pList == NULL)
	{
		printf("clearDoublyList() : invalid argument\n");
		return ;
	}
	while (removeDLElement(pList, 0))
		;
}

int	getDoublyListLength(DoublyList *pList)
{
	if (pList == NULL)
	{
		printf("getDoublyListLength() : invalid argument\n");
		return (FALSE);
	}
	return (pList->currentElementCount);
}

DoublyListNode	*getDLElement(DoublyList *pList, int position)
{
	DoublyListNode	*curr;

	if (pList == NULL || position < 0 || position >= pList->currentElementCount)
	{
		printf("getDLElement() : invalid argument\n");
		return (NULL);
	}
	curr = pList->headerNode.pRLink;
	while (position > 0)
	{
		curr = curr->pRLink;
		position--;
	}
	return (curr);
}

void	displayDoublyList(DoublyList *pList)
{
	int			iValue;
	int			iIndex;
	int			count;
	const int	NUMBERS_PER_LINE = 5;
	DoublyListNode	*curr;

	if (pList == NULL)
	{
		printf("displayDoublyList() : invalid argument\n");
		return ;
	}
	curr = pList->headerNode.pRLink;
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
		curr = curr->pRLink;
		iValue++;
	}
}
