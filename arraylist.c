#include <stdlib.h>
#include <stdio.h>
#include "arraylist.h"

ArrayList*	createArrayList(int maxElementCount)
{
	ArrayList	*newList;

    if (maxElementCount <= 0)
    {
        printf("createArrayList(): invalid argument\n");
        return (NULL);
    }
	newList = malloc(sizeof(ArrayList));
	if (newList == NULL)
    {
        printf("createArrayList(): malloc failed\n");
		return (NULL);
    }
	newList->maxElementCount = maxElementCount;
	newList->currentElementCount = 0;
	newList->pElement = malloc(sizeof(ArrayListNode) * maxElementCount);
	if (newList->pElement == NULL)
	{
        printf("createArrayList(): malloc failed\n");
		free(newList);
		return (NULL);
	}
	return (newList);
}

void	deleteArrayList(ArrayList** pList)
{
    if (pList == NULL || *pList == NULL)
    {
        printf("deleteArrayList(): invalid argument\n");
        return ;
    }
	free((*pList)->pElement);
	free(*pList);
	*pList = NULL;
}

int	isArrayListFull(ArrayList *pList)
{
    if (pList == NULL)
    {
        printf("isArrayListFull(): invalid argument\n");
        return (FALSE);
    }
	return (pList->maxElementCount == pList->currentElementCount);
}

int	addALElement(ArrayList *pList, int position, ArrayListNode element)
{
	int	i;

	if (pList == NULL
        || isArrayListFull(pList)
        || position < 0
        || position > pList->currentElementCount)
    {
        printf("addALElement(): invalid argument\n");
		return (FALSE);
    }
	i = pList->currentElementCount;
	while (i > position)
	{
		pList->pElement[i] = pList->pElement[i - 1];  
		i--;
	}
	pList->pElement[i] = element;
	pList->currentElementCount++;
	return (TRUE);
}

int	removeALElement(ArrayList *pList, int position)
{
	int	i;

	if (pList == NULL
        || pList->currentElementCount == 0
        || position < 0
        || position >= pList->currentElementCount)
    {
        printf("removeALElement(): invalid argument\n");
		return (FALSE);
    }
	i = position;
	while (i < pList->currentElementCount - 1)
	{
		pList->pElement[i] = pList->pElement[i + 1];
		i++;
	}
	pList->currentElementCount--;
	return (TRUE);
}

ArrayListNode *getALElement(ArrayList *pList, int position)
{
	if (pList == NULL
        || position < 0
        || position >= pList->currentElementCount)
    {
        printf("getALElement(): invalid argument\n");
		return (NULL);
    }
	return (&pList->pElement[position]);
}

void	displayArrayList(ArrayList *pList)
{
	int			iValue;
	int			iIndex;
	int			count;
	const int	NUMBERS_PER_LINE = 5;

    if (pList == NULL)
    {
        printf("displayArrayList(): invalid argument\n");
        return ;
    }
	iValue = 0;
	iIndex = 0;
	while (iValue < pList->maxElementCount)
	{
		if (iValue < pList->currentElementCount)
			printf(" %9d |", pList->pElement[iValue].data);
		else
			printf("         x |");
		if (iValue % NUMBERS_PER_LINE == NUMBERS_PER_LINE - 1 
			|| iValue + 1 == pList->maxElementCount)
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
		iValue++;
	}
}

void	clearArrayList(ArrayList *pList)
{
    if (pList == NULL)
    {
        printf("clearArrayList(): invalid argument\n");
        return ;
    }
	pList->currentElementCount = 0;
}

int	getArrayListLength(ArrayList *pList)
{
    if (pList == NULL)
    {
        printf("getArrayListLength(): invalid argument\n");
        return (-1);
    }
	return (pList->currentElementCount);
}
