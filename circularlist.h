#ifndef _CIRCULARLIST_
#define _CIRCULARLIST_

typedef struct ListNodeType
{
	int data;
	struct ListNodeType* pLink;
} ListNode;

typedef struct LinkedListType
{
	int currentElementCount;	// ���� ����� ������ ����
	ListNode *tail;		// ��� ���(Header Node)
} LinkedList;

LinkedList* createCLList();
int addCLElement(LinkedList* pList, int position, ListNode element);
int	addCLElementBack(LinkedList* pList, ListNode element);
int removeCLElement(LinkedList* pList, int position);
ListNode* getCLElement(LinkedList* pList, int position);

void clearCLList(LinkedList* pList);
int getCLListLength(LinkedList* pList);
void deleteCLList(LinkedList* pList);
void displayCircularList(LinkedList* pList);
#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0

#endif
