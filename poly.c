#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "poly.h"

static int	attach(polyNode **pList, int coef, int expon)
{
	polyNode	*curr;
	polyNode	*newNode;

	if (pList == NULL || expon < 0)
	{
		printf("attach() : invalid argument\n");
		return (FALSE);
	}
	newNode = malloc(sizeof(polyNode));
	if (newNode == NULL)
	{
		printf("pRead() : malloc failed\n");
		return (FALSE);
	}
	newNode->coef = coef;
	newNode->expon = expon;
	newNode->pLink = NULL;
	curr = *pList;
	if (curr == NULL)
		*pList = newNode;
	else
	{
		while (curr->pLink != NULL)
			curr = curr->pLink;
		curr->pLink = newNode;
	}
	return (TRUE);
}

static int	pow(int x, int expon)
{
	int	ret;

	ret = 1;
	while (expon > 0)
	{
		ret *= x;
		expon--;
	}
	return (ret);
}

polyNode	*pRead(int n, ...)
{
	int			c;
	va_list		ap;
	polyNode	*list;
	polyNode	*newNode;

	va_start(ap, n);
	list = NULL;
	while (n + 1 > 0)
	{
		c = va_arg(ap, int);
		if (c != 0)
		{
			if (attach(&list, c, n) == FALSE)
			{
				printf("pRead() : attach failed\n");
				pErase(list);
				return (NULL);
			}
		}
		n--;
	}
	va_end(ap);
	return (list);
}

void	pWrite(polyNode *pList)
{
	polyNode	*curr;

	if(pList == NULL)
	{
		printf("pWrite() : invalid argument\n");
		return ;
	}
	printf("(%d)x^%d", pList->coef, pList->expon);
	curr = pList->pLink;
	while(curr != NULL)
	{
		if(curr->expon == 0)
			printf(" + (%d)", curr->coef);
		else
			printf(" + (%d)x^%d", curr->coef, curr->expon);
		curr = curr->pLink;
	}
	printf("\n");
}

polyNode	*pAdd(polyNode *a, polyNode *b)
{
	polyNode	*c;
	int			expon;
	int			coef;

	if(a == NULL || b == NULL)
	{
		printf("pAdd() : invalid argument\n");
		return (NULL);
	}
	c = NULL;
	while(a != NULL && b != NULL)
	{
		if(a->expon > b->expon)
		{
			expon = a->expon;
			coef = a->coef;
			a = a->pLink;
		}
		else if(a->expon < b->expon)
		{
			expon = b->expon;
			coef = b->coef;
			b = b->pLink;
		}
		else
		{
			expon = a->expon;
			coef = a->coef + b->coef;
			a = a->pLink;
			b = b->pLink;
		}
		if(attach(&c, coef, expon) == FALSE)
		{
			printf("pAdd() : attach failed\n");
			pErase(c);
			return (NULL);
		}
	}
	while(a != NULL)
	{
		if(attach(&c, a->coef, a->expon) == FALSE)
		{
			printf("pAdd() : attach failed\n");
			pErase(c);
			return (NULL);
		}
		a = a->pLink;
	}
	while(b != NULL)
	{
		if(attach(&c, b->coef, b->expon) == FALSE)
		{
			printf("pAdd() : attach failed\n");
			pErase(c);
			return (NULL);
		}
		b = b->pLink;
	}
	return (c);
}

int	pEval(polyNode *pList, int x)
{
	int	ret;

	if (pList == NULL)
	{
		printf("pEval() : invalid argument\n");
		return (0);
	}
	ret = 0;
	while (pList != NULL)
	{
		ret += pow(x, pList->expon) * pList->coef;
		pList = pList->pLink;
	}
	return (ret);
}

void	pErase(polyNode *pList)
{
	polyNode	*toDelete;

	toDelete = pList;
	while(pList != NULL)
	{
		pList= toDelete->pLink;
		free(toDelete);
		toDelete = pList;
	}
}
