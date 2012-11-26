/************************************************************************/
//���ݽṹ�ڶ��£��й�˫����������Ĳ���
//����ʱ�䣺2011/7/08
//���ߣ�Ϳ��
/************************************************************************/

#include <stdlib.h>		//malloc������������ж����
#include <stdio.h>		//printf,scanf������������ж����
#include <string.h>		//memset������������ж����
#include "DList.h"
/************************************************************************/
// ��˫�������ʼ��������Ԫ��Ϊn�����ǳɹ�����1�����򷵻�0
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
// ��˫��������λ��i����Ԫ��e�����ǳɹ�����1�����򷵻�0
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
	}//������λ��i֮ǰ��Ԫ��

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
// ɾ��˫��������λ��iԪ�أ���ͨ��e���أ����ǳɹ�����1�����򷵻�0
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
	}//������λ��i֮ǰ��Ԫ��
	
	DeletDLNode = p->next;

	p->next = DeletDLNode->next;
	DeletDLNode->next->prior = p;
	*e = DeletDLNode->data;
	free( DeletDLNode );
	return OK;
}

/************************************************************************/
// ��˫������L�еĵ�i������Ԫ�ط��ظ�e
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
// �����������Ԫ�ص�ָ�붼��ӡ���������ǳɹ�����1�����򷵻�0
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
	}//������λ��i֮ǰ��Ԫ��
	return OK;
}
/************************************************************************/
//�����Ա�ĸ������ܺ���������
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
