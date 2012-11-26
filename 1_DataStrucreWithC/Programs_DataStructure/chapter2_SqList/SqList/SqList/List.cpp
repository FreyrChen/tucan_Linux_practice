/************************************************************************/
//���ݽṹ�ڶ��£��й���������Ĳ���
//����ʱ�䣺2011/7/05
//���ߣ�Ϳ��
/************************************************************************/
#include"List.h"
#include <stdlib.h>		//malloc������������ж����
#include <stdio.h>		//scanf������������ж����
/************************************************************************/
// ��λ������n��Ԫ�ص�ֵ������ͷ���ΪL�ĵ���������P30
/************************************************************************/
void CreatList_L( LinkList &L, int n)
{
	int i;
	LinkList p;
	
	//�Ƚ��������һ��β�ڵ�
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
// ��������L�еĵ�i������Ԫ�ط��ظ�e��P29
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
// ��ͷ���ָ��ΪL�ĵ����������еĵ�i��λ��֮ǰ����Ԫ��e,P29
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
	}//������λ��i֮ǰ��Ԫ��
	if( !p || j>i-1 ) return ERROR;

	S = (LinkList) malloc( sizeof(LNode) );
	S->data = e;	//�����½ڵ�
	S->next = p->next;
	p->next = S;
	return OK;
}
/************************************************************************/
// ��ͷ���ָ��ΪL�ĵ����������еĵ�i��λ�õ�Ԫ��ɾ��,���ҷ���ɾ����Ԫ��e,P30
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
//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P31
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
			pc = pa;		//��PCָ������ƶ�һ���ڵ�
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;		//��PCָ������ƶ�һ���ڵ�
			pb = pb->next;
		}
	}
	pc->next = pa ? pa:pb;	//����ʣ��ڵ�
	free (Lb);
}


/************************************************************************/
// ������������Lb�еĵ�����La�е�����Ԫ�ز��뵽La�У�P20
/************************************************************************/
/*
void Union (List &La, List Lb)
{
	int i,e;	//��ʱֵ
	int La_len, Lb_len;	//���Ա���

	La_len = ListLenth( La );	// �����Ա���
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
//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P21
/************************************************************************/
/*void MergeList( List La, List Lb, List &Lc )
{
	InitList( Lc );
	i = 1;  j = 1;
	k = 0;
	La_len = ListLength( La );
	Lb_len = ListLength( Lb );
	//�Ƚ���ͬλ�õ�Ԫ�ش�С
	while( ( i<=La_len ) && ( j<=Lb_len ) )
	{	//La��Lb���ǿ�ʱ
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
	//�ϳ������ʣ��Ԫ��һ�β���
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

//�����Ա�ĸ������ܺ���������
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