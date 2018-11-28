#pragma once

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

typedef int DataType;

typedef struct SListNode
{
	struct SListNode* next;
	DataType data;
}SListNode;

SListNode* BuySListNode(DataType x)
{
	SListNode* node = (SListNode*)malloc(sizeof(SListNode));
	assert(node);
	node->data = x;
	node->next = NULL;

	return node;
}

void SListPushBack(SListNode** ppHead, DataType x)
{
	if (*ppHead == NULL)
	{
		*ppHead = BuySListNode(x);
	}
	else
	{
		SListNode* cur = *ppHead;
		while (cur->next!=NULL)
		{
			cur = cur->next;
		}
		cur->next = BuySListNode(x);
	}
}

void SListPopBack(SListNode** ppHead)
{
	if (*ppHead==NULL)
	{
		return;
	}
	else if ((*ppHead)->next==NULL)
	{
		free(*ppHead);
		*ppHead = NULL;
	}
	else
	{
		SListNode* cur = *ppHead;
		SListNode* prve = NULL;//prve记录被删除节点的前一个节点
		while (cur->next!=NULL)
		{
			prve = cur;
			cur = cur->next;
		}
		printf("%d\n",cur->data);
		free(cur);
		prve->next = NULL;
	}
}

void SListPrint(SListNode* pHead)
{
	SListNode* cur = pHead;
	while (cur!=NULL)
	{
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

SListNode* SListFind(SListNode* pHead,DataType x)
{
	if (pHead==NULL)
	{
		return;
	}
	SListNode* cur=pHead;
	
	while (cur->next!=NULL)
	{
		if (cur->data==x)
		{
			return cur;
		}
		cur = cur->next;
		
	}
	return ;
	
}


//面试题
//从尾到头打印链表
void SListReversePrint(SListNode* pHead)
{
	SListNode* end = NULL;//存放要打印的节点的后一个节点；
	while (end!=pHead)
	{
		SListNode* cur = pHead;
		while (cur->next!= end)
		{		
			cur = cur->next;
		}
		printf("%d ", cur->data);
		end = cur;	
	}
	printf("\n");
}
void SListReversePrintR(SListNode* pHead)
{
	if (pHead==NULL)
	{
		return;
	}
	SListReversePrintR(pHead->next);
	printf("%d ",pHead->data);
}
//删除一个无头单链表的非尾节点
void SListPopNoHead(SListNode* pos)
{
	SListNode* cur;
	assert(pos&&pos->next);
	//替换法删除
	cur = pos->next;
	pos->next = cur->next;
	pos->data = cur->data;
	free(cur);
}
//在无头单链表的一个节点前插入一个节点（不能遍历链表）
void SListPushNoHead(SListNode* pos,DataType x)
{
	SListNode* cur;
	assert(pos);
	cur = BuySListNode(pos->data);
	cur->next = pos->next;
	pos->next = cur;
	cur->data = pos->data;
	pos->data = x;
}
//约瑟夫环
SListNode* SListJoseph(SListNode* pHead,int k)
{
	SListNode* tail= pHead;
	if (pHead == NULL)
	{
		return;
	}
	//构成环
	while(tail->next!=NULL)
	{
		tail = tail->next;
	}
	tail->next = pHead;
	//判断
	SListNode* cur = pHead;
	while (cur->next!=cur)
	{
		int count = k;
		while (--count)
		{
			cur = cur->next;		
		}
		SListNode* nextNode = cur->next;
		cur->data = nextNode->data;
		cur->next = nextNode->next;
		free(nextNode);
	}
	return cur;
}
//逆置/反转单链表
SListNode* SListReverse1(SListNode* pHead)
{
	if (pHead==NULL||pHead->next==NULL)
	{
		return pHead;
	}
	SListNode* n1, *n2, *n3;
	n1 = pHead;
	n2 = n1->next;
	n3 = n2->next;
	while (n2!=NULL)
	{
		n2->next = n1;
		n1 = n2;
		n2 = n3;
		if (n3)
		{
			n3 = n3->next;
		}		
	}
	pHead->next = NULL;
	pHead = n1;

	return pHead;
}
SListNode* SListReverse2(SListNode* pHead)
{
	if (pHead==NULL||pHead->next==NULL)
	{
		return pHead;
	}
	else
	{
		SListNode* NewNode = NULL;
		SListNode* cur = pHead;
		while (cur)
		{
			SListNode* temp = cur;
			cur = cur->next;

			temp->next = NewNode;
			NewNode = temp;
		}
		return NewNode;
	}
	
}
//单链表排序（冒泡、快速）
void SListBUbbleSort(SListNode* head)
{
	SListNode* front, *back;
	SListNode* tail = NULL;
	if (head==NULL||head->next==NULL)
	{
		return head;
	}
	while (tail!=head->next)
	{
		int flag = 0;
		front = head;
		back = front->next;
		while (back != tail)
		{
			if (front->data > back->data)
			{
				DataType temp = front->data;
				front->data = back->data;
				back->data = temp;
				flag = 1;
			}
			front = front->next;
			back = back->next;
		}	
		if (flag==0)
		{
			break;
		}
		tail = front;
	}
	
}
//合并两个链表，合并后依然有序
SListNode* SListMerge(SListNode* list1,SListNode* list2)
{
	SListNode* newList;
	SListNode* tail;
	if (list1==NULL)
	{
		return list2;
	}
	if (list2==NULL)
	{
		return list1;
	}
	if (list1->data<list2->data)
	{
		newList = list1;
		list1 = list1->next;
	}
	else
	{
		newList = list2;
		list2 = list2->next;
	}
	tail = newList;
	while (list1&&list2)
	{
		if (list1->data<list2->data)
		{
			tail->next = list1;
			list1 = list1->next;
		}
		else
		{
			tail->next = list2;
			list2 = list2->next;
		}
		tail = tail->next;
	}
	if (list1)
	{
		tail->next = list1;
	}
	if (list2)
	{
		tail->next = list2;
	}
	return newList;
}
//查找单链表的中间节点，要求只能遍历一次链表
SListNode* SListMidNode(SListNode** head)
{
	SListNode* cur, *curTwo;
	if (head==NULL)
	{
		return;
	}
	cur = *head;
	curTwo = *head;
	while (curTwo->next!=NULL&&curTwo)
	{
		cur = cur->next;
		curTwo = curTwo->next->next;
	}
	return cur;
}
//查找单链表的倒数第K个节点，要求只能遍历一次链表
SListNode* SLNode(SListNode** head,DataType k)
{
	SListNode* fast = NULL;
	SListNode* slow = NULL;
	fast = *head;
	slow = *head;
	if (*head==NULL||k==0)
	{
		return;
	}
	for (int i = 0; i < k - 1;i++)
	{
		if (fast->next!=NULL)
		{
			fast = fast->next;
		}
		else
		{
			return;
		}
	}
	while (fast->next!=NULL)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}
//删除倒数第K个节点

//判断单链表是否带环？若带环，求环的长度？求环的入口？并讨论每个算法的时间&空间复杂度


void SListTest()
{
	SListNode* list=NULL;
	SListPushBack(&list, 1);
	SListPushBack(&list, 2);
	SListPushBack(&list, 3);
	SListPushBack(&list, 4);
	SListPrint(list);

	SListReversePrint(list);
	SListReversePrintR(list);
	printf("\n");
	printf("-------------------\n");

	SListNode* pos = NULL;
	SListNode* list2 = NULL;
	SListPushBack(&list2, 1);
	SListPushBack(&list2, 2);
	SListPushBack(&list2, 3);
	SListPushBack(&list2, 4);
	SListPushBack(&list2, 5);
	SListPrint(list2);

	pos = SListFind(list2,3);
	SListPopNoHead(pos);
	SListPrint(list2);

	pos = SListFind(list2,4);
	SListPushNoHead(pos,6);
	SListPrint(list2);
	printf("-------------------\n");

	SListNode* list3 = NULL;
	SListNode* pos3 = NULL;
	SListPushBack(&list3, 1);
	SListPushBack(&list3, 2);
	SListPushBack(&list3, 3);
	SListPushBack(&list3, 4);
	SListPushBack(&list3, 5);
	SListPushBack(&list3, 6);
	SListPushBack(&list3, 7);
	SListPrint(list3);

	pos3=SListJoseph(list3,3);
	printf("幸存者：%d\n",pos3->data);
	printf("-------------------\n");

	SListNode* list4 = NULL;
	SListPushBack(&list4, 1);
	SListPushBack(&list4, 2);
	SListPushBack(&list4, 3);
	SListPushBack(&list4, 4);
	SListPushBack(&list4, 5);
	SListPrint(list4);

	SListNode* newList = NULL;
	newList = SListReverse2(list4);
	SListPrint(newList);
	printf("-------------------\n");

	SListNode* list5 = NULL;
	SListPushBack(&list5, 5);
	SListPushBack(&list5, 2);
	SListPushBack(&list5, 9);
	SListPushBack(&list5, 1);
	SListPushBack(&list5, 3);
	SListPushBack(&list5, 4);
	SListPushBack(&list5, 7);
	SListPushBack(&list5, 0);
	SListPrint(list5);

	SListBUbbleSort(list5);
	SListPrint(list5);
	printf("-------------------\n");

	SListNode* listOne = NULL;
	SListPushBack(&listOne, 0);
	SListPushBack(&listOne, 2);
	SListPushBack(&listOne, 3);
	SListPushBack(&listOne, 6);
	SListPushBack(&listOne, 7);
	SListPushBack(&listOne, 9);
	SListPrint(listOne);

	SListNode* listTwo = NULL;
	SListPushBack(&listTwo, 1);
	SListPushBack(&listTwo, 2);
	SListPushBack(&listTwo, 4);
	SListPushBack(&listTwo, 5);
	SListPushBack(&listTwo, 8);
	SListPushBack(&listTwo, 10);
	SListPushBack(&listTwo, 12);
	SListPushBack(&listTwo, 15);
	SListPrint(listTwo);

	SListNode* ListOT = NULL;
	ListOT = SListMerge(listOne,listTwo);
	SListPrint(ListOT);
	printf("-------------------\n");

	SListNode* list7 = NULL;
	SListPushBack(&list7, 1);
	SListPushBack(&list7, 2);
	SListPushBack(&list7, 3);
	SListPushBack(&list7, 4);
	SListPushBack(&list7, 5);
	SListPushBack(&list7, 6);
	SListPushBack(&list7, 7);
	SListPushBack(&list7, 8);
	SListPrint(list7);
	SListNode* midNode = NULL;
	midNode = SListMidNode(list7);
	printf("中间节点为：%d\n",midNode->data);
	SListNode* DaoShuNode = NULL;
	DaoShuNode = SLNode(&list7,4);
	printf("倒数第k个节点为：%d\n",DaoShuNode->data);
	printf("-------------------\n");
	
}