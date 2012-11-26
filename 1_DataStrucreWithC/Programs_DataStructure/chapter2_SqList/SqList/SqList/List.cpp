/************************************************************************/
//数据结构第二章，有关线性链表的操作
//创建时间：2011/7/05
//作者：涂灿
/************************************************************************/
#include"List.h"
#include <stdlib.h>		//malloc函数在这个库中定义的
#include <stdio.h>		//scanf函数在这个库中定义的
/************************************************************************/
// 逆位序输入n个元素的值，建立头结点为L的但线性链表，P30
/************************************************************************/
void CreatList_L( LinkList &L, int n)
{
	int i;
	LinkList p;
	
	//先建立了最后一个尾节点
	L = ( LinkList ) malloc( sizeof(LNode) );
	L->next = NULL;

	for( i = n; i>0; --i)
	{
		p = ( LinkList ) malloc( sizeof(LNode) );
		scanf( "%d",&p->data );
		//printf("%d\n",p->data);
		p->next = L->next;
		L->next = p;

	}
}

/************************************************************************/
// 将单链表L中的第i个数据元素返回给e，P29
/************************************************************************/
Status GetElem_L( LinkList L, int i, ElemType &e)
{
	LinkList p;
	int j;

	p = L->next;
	j = 1;
	while( p && j<i )
	{
		p = p->next;
		++j;
	}
	if( !p || j>i )	return ERROR;
	e = p->data;
	//printf("%d \n",e);
	return OK;		
}

/************************************************************************/
// 将头结点指针为L的单线性链表中的第i个位置之前插入元素e,P29
/************************************************************************/	
Status ListInsert_L( LinkList &L, int i,ElemType e)
{
	int j;
	LinkList p;
	LNode *S;
	
	p = L->next;
	j =1;
	while( p && j<(i-1) )
	{
		p = p-> next;
		++j;
	}//遍历到位置i之前的元素
	if( !p || j>i-1 ) return ERROR;

	S = (LinkList) malloc( sizeof(LNode) );
	S->data = e;	//创造新节点
	S->next = p->next;
	p->next = S;
	return OK;
}
/************************************************************************/
// 将头结点指针为L的单线性链表中的第i个位置的元素删除,并且返回删除的元素e,P30
/************************************************************************/	
Status ListDelet_L( LinkList &L, int i,ElemType &e)
{
	int j;
	LinkList p;
	LinkList DeletLNode;

	p = L->next;
	j =1;
	while( p && j<(i-1) )
	{
		p = p-> next;
		++j;
	}
	if( !p || j>i-1 ) return ERROR;
	DeletLNode = p->next;
	p->next = DeletLNode->next;
	e = DeletLNode->data;
	free(DeletLNode);
	return OK;
}
/************************************************************************/
//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P31
/************************************************************************/
void MergeList_L( LinkList &La, LinkList &Lb, LinkList &Lc )
{
	LinkList pa,pb,pc;
	
	pa = La->next;	pb = Lb->next;
	Lc = pc = La;
	while( pa && pb )
	{
		if ( pa->data <= pb->data )
		{
			pc->next = pa;	
			pc = pa;		//将PC指针向后移动一个节点
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;		//将PC指针向后移动一个节点
			pb = pb->next;
		}
	}
	pc->next = pa ? pa:pb;	//插入剩余节点
	free (Lb);
}


/************************************************************************/
// 将所有在链表Lb中的但不在La中的数据元素插入到La中，P20
/************************************************************************/
/*
void Union (List &La, List Lb)
{
	int i,e;	//临时值
	int La_len, Lb_len;	//线性表长度

	La_len = ListLenth( La );	// 求线性表长度
	Lb_len = ListLenth( Lb );
	for( i=1; i<= Lb_len; i++)
	{
		GetElem(Lb, i, e);
		if( !LocateElem( La, e, equal ) ) 
		ListInsert( La, ++La_len, e );
	}

}
*/

/************************************************************************/
//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P21
/************************************************************************/
/*void MergeList( List La, List Lb, List &Lc )
{
	InitList( Lc );
	i = 1;  j = 1;
	k = 0;
	La_len = ListLength( La );
	Lb_len = ListLength( Lb );
	//比较相同位置的元素大小
	while( ( i<=La_len ) && ( j<=Lb_len ) )
	{	//La和Lb均非空时
		GetElem( La, i, ai );
		GetElem( Lb, j, bj );
		if( ai<= bj )
		{
			ListInsert( Lc, ++k, ai );
			++i;
		}
		else
		{
			ListInsert( Lc, ++k, bj );
			++j;
		}
	}
	//较长链表的剩余元素一次插入
	while( i<= La_len )
	{
		GetElem( La, i++, ai );
		ListInsert( Lc, ++k, ai);
	}
	while( j <= Lb_len )
	{
		GetElem( Lb, j++, bj );
		ListInsert( Lc, ++k, bj );
	}
}
*/

//对线性表的各个功能函数做测试
void ListTest()
{
	LinkList La,Lb,Lc;
	int i;
	ElemType temp;

	LinkList p;
	int j;

	CreatList_L( La, 5);
	printf("the list is:");
	for ( i=1; i<6; i++ )
	{
		GetElem_L( La, i, temp );
		printf("%d ",temp);
	}

	if ( ListInsert_L( La, 3,77) )
	{
		printf("\nthe insert list is:");
		for ( i=1; i<7; i++ )
		{
			GetElem_L( La, i, temp );
			printf("%d ",temp);
		}
	}
	
	if ( ListDelet_L( La, 3,temp) )
	{
		printf("\nthe delet list is:");
		for ( i=1; i<6; i++ )
		{
			GetElem_L( La, i, temp );
			printf("%d ",temp);
		}
	}

	
	CreatList_L( Lb, 5);
	printf("\n the list a is:");
	for ( i=1; i<6; i++ )
	{
		GetElem_L( La, i, temp );
		printf("%d ",temp);
	}
	printf("\n the list b is:");
	for ( i=1; i<6; i++ )
	{
		GetElem_L( Lb, i, temp );
		printf("%d ",temp);
	}
	MergeList_L( La, Lb, Lc);
	printf("\n the list c is:");
	for ( i=1; i<11; i++ )
	{
		GetElem_L( Lc, i, temp );
		printf("%d ",temp);
	}


}