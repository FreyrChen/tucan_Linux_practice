/************************************************************************/
//数据结构第二章，有关双向线性链表的操作
//创建时间：2011/7/08
//作者：涂灿
/************************************************************************/

#include <stdlib.h>		//malloc函数在这个库中定义的
#include <stdio.h>		//printf,scanf函数在这个库中定义的
#include <string.h>		//memset函数在这个库中定义的
#include "DList.h"
/************************************************************************/
// 在双向链表初始化，链表元素为n，若是成功返回1，否则返回0
/************************************************************************/
Status InitDLinkList( DLinkList &L ,int n)
{
	int i;
	DLinkList p;

	L =(  DLinkList ) malloc( sizeof( DLinkNode) );
	if( !L  )	return OVERFLOW;
	
	//memset( &(L->data), 0, sizeof( DataType));
	L->next = L->prior = NULL;
	printf("please in put %d element of DLinkList:\n",n);
	for( i = n; i>0; --i)
	{
		p = (  DLinkList ) malloc( sizeof( DLinkNode) );
		scanf( "%d",&p->data );
		//printf("%d\n",p->data);
		p->next = L->next;
		L->next = p;
		p->prior = L;

	}
	return OK;		
}


/************************************************************************/
// 在双向链表中位置i插入元素e，若是成功返回1，否则返回0
/************************************************************************/
Status InsertDLinkList( DLinkList &L, int i, DataType e)
{
	DLinkNode *p, *s;
	int j;

	p = L;
	j=1;
	while( p && j<i )
	{
		p = p-> next;
		++j;
	}//遍历到位置i之前的元素

	s =( DLinkNode* ) malloc( sizeof( DLinkNode) );
	if( !s  )	return OVERFLOW;
	s->data = e;
	s->next = p->next;
	p->next->prior = s;
	p->next = s;
	s->prior = p;
	return OK;
}

/************************************************************************/
// 删除双向链表中位置i元素，并通过e返回，若是成功返回1，否则返回0
/************************************************************************/
Status DeleteLinkList( DLinkList &L, int i, DataType *e)
{
	DLinkNode *p, *DeletDLNode;
	int j;

	p = L->next;
	j=1;
	while( p && j<(i-1) )
	{
		p = p-> next;
		++j;
	}//遍历到位置i之前的元素
	
	DeletDLNode = p->next;

	p->next = DeletDLNode->next;
	DeletDLNode->next->prior = p;
	*e = DeletDLNode->data;
	free( DeletDLNode );
	return OK;
}

/************************************************************************/
// 将双向链表L中的第i个数据元素返回给e
/************************************************************************/
Status GetElem_DL( DLinkList L, int i,  DataType *e)
{
	DLinkNode *p;
	int j;

	p = L->next;
	j = 1;
	while( p && j<i )
	{
		p = p->next;
		++j;
	}
	if( !p || j>i )	return ERROR;
	*e = p->data;
	//printf("%d \n",e);
	return OK;		
}

/************************************************************************/
// 将链表的所有元素的指针都打印出来，若是成功返回1，否则返回0
/************************************************************************/
Status	PrintDLinkList( DLinkList L)
{
	DLinkNode *p;
	int j;

	p = L;
	j=1;
	while( p->next )
	{
		p = p-> next;
		printf("NO.%d Address: %p,Pri:%p,Value: %d,Next:%p\n", j,p,p->prior,p->data,p->next);
		++j;
	}//遍历到位置i之前的元素
	return OK;
}
/************************************************************************/
//对线性表的各个功能函数做测试
/************************************************************************/
void DListTest()
{
	DLinkList La;
	DataType deletelem;
	int i;

	if( InitDLinkList(La,3))
	{
		 InsertDLinkList( La,1,7);
		 InsertDLinkList( La,1,8);
		 InsertDLinkList( La,5,9);

	}

	PrintDLinkList( La);
    DeleteLinkList( La, 3, &deletelem);
	printf("the delete valaue is :%d\nthe new list is :\n",deletelem);
	PrintDLinkList( La);
	
	printf("\nuse get element from lis ,the value is: ");
	for(i=1;i<6;i++)
	{
		GetElem_DL( La, i, &deletelem);
		printf("\n%d",deletelem);
	}
}
