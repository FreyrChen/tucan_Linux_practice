
/************************************************************************/
//���ݽṹ�ڶ��£��й�˳������Ĳ���
//����ʱ�䣺2011/7/03
//���ߣ�Ϳ��
/************************************************************************/
//=======================˳�����Ա�=============

#include"SqList.h"
#include <stdlib.h> //malloc������������ж����
#include <stdio.h>		//printf������������ж����
/************************************************************************/
// ����һ���յ���������P23
/************************************************************************/
#define LIST_INIT_SIZE	100	//���Ա�洢�ռ�ĳ�ʼ��������
#define LISTINCREMENT	10	//���Ա�洢�ռ�ķ�������

Status InitList_Sq( SqList &L )
{
	L.elem = (int *)malloc( LIST_INIT_SIZE*sizeof( ElemType) );
	if( !L.elem )
		exit( OVERFLOW );
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}

/************************************************************************/
// ��˳�����Ա�L�еĵ�i��λ��֮ǰ�����µ�Ԫ��e��P24
/************************************************************************/
Status ListInsert_Sq( SqList &L, int i, ElemType e)
{
	ElemType *p;
	ElemType *q;
    ElemType *newbase;

	// �ȼ�����λ�õĺϷ���
	if( !( (i>=1) && i<=( L.length + 1 ) ))
		return ERROR;
	if( L.length >= L.listsize )
	{	//  ����ǰ�洢�ռ������������ӷ���ռ�
		//������ԭ������ĺ������ӣ��п��ܺ���ĵ�ַ�Ѿ���ռ��
		//��Ҫ���µ��ڴ����򻮷ֳ��ܴ�����������Ŀռ�
		newbase = ( ElemType *)realloc( L.elem, 
							(L.listsize + LISTINCREMENT) * sizeof( ElemType ) );
		if( !newbase)			//	���洢����ʧ��
			exit( OVERFLOW );
		L.elem = newbase;		//�»���ַ
		L.listsize += LISTINCREMENT;	// ���Ӵ洢����
	}
	q = &( L.elem[i-1]);		// qΪ����λ��
	for( p = &( L.elem[L.length - 1] ); p >= q; --p )
		*(p+1) = *p;		// ����λ��֮���Ԫ�������ƶ�
	*q = e;					//������Ԫ��e
	++L.length;				//	������
	return OK;
}

Status ListLenth( SqList &L )
{
	return L.length;
}


/************************************************************************/
//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P26
/************************************************************************/
void MergeList_sq( SqList La, SqList Lb, SqList &Lc )
{
	int *pa; 
	int	*pb;
	int	*pc;
	int *pa_last;
	int *pb_last;

	pa = La.elem;
	pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = ( ElemType* ) malloc ( Lc.listsize*sizeof(ElemType) );
	if( !Lc.elem ) exit( OVERFLOW );
	pa_last = La.elem + La.length - 1;
	pb_last = Lb.elem + Lb.length - 1;
	while( pa <= pa_last && pb<= pb_last )
	{
		if( *pa <= *pb ) *pc++ = *pa++;
		else *pc++ = *pb++;
	}
	//	����LA����LBʣ�µ�Ԫ��
	while( pa<= pa_last ) *pc++ = *pa++;
	while( pb<= pb_last ) *pc++ = *pb++;
}



/************************************************************************/
// ��˳�����Ա�L��ɾ����i��λ�õ�Ԫ�أ�����e������ֵ��P24
/************************************************************************/
Status ListDelete_Sq( SqList &L, int i, ElemType &e)
{
	 ElemType *p;
	 ElemType *q;


	//�ȼ��ɾ��λ��i�ĺϷ���
	if( (i>=1) && ( i<=L.length) )
	{	
		p = &( L.elem[i-1] );		//	pΪ��ɾ��Ԫ��λ�ã�
		e = *p;						//	��ɾ��Ԫ�ص�ֵ����e
		q = L.elem + L.length - 1;	//	��βԪ�ص�λ��
		for( ++p; p<=q; ++p )		//	ɾ��Ԫ��֮���Ԫ������ǰ��
			*( p-1 ) = *p;
		--L.length;					//	����С
		return OK;
	}
	else
	return ERROR;
}


// �Ƚ��������Ĵ�С
Status compare( ElemType a, ElemType b )
{
	if ( a >= b )	return 0;
	else	return 1;
}


/************************************************************************/
// ��˳�����Ա�L�в��ҵ�һ����e����compare������Ԫ�ص�λ�ã�P26
/************************************************************************/
Status LocateElem_Sq( SqList L,  ElemType e,
					 Status( *compare )( ElemType, ElemType ))
{	//	���ҵ����򷵻�����L�е�λ�ã����򷵻�0
	ElemType  i;
	ElemType *p;

	i = 1;			//	i�ĳ�ֵΪ��һ��Ԫ�ص�λ��
	p = L.elem;		//	p�ĳ�ֵΪ��һ��Ԫ�صĴ洢λ��
	while( i <= L.length && ( *compare )( *p++, e ))
		++i;
	if( i<= L.length )
		return i;
	else return 0;
}


//��˳������������ܺ����Ĳ���
void SqLsitTest()
{

	int i;
	int a[5]={1,2,3,5,8};
	int b[5]={4,6,8,9,0};
	ElemType temp;
	

	SqList La,Lb,Lc;

	InitList_Sq( La );
	InitList_Sq( Lb );
	InitList_Sq( Lc );

	for ( i=1;i< 6; i++)
		ListInsert_Sq( La,i,a[i-1]);
	for ( i=1;i< 6; i++)
		ListInsert_Sq( Lb,i,b[i-1]);

	//ListDelete_Sq( &Lb, 4, delet );
	//printf("\n the delete is: %d \n", delet);
	
	for(i=0;i <5; i++)
	{
		printf( "addr:%p, value: %d   ",&(La.elem[i]),La.elem[i]);
		printf( "addr:%p, value: %d\n",&(Lb.elem[i]),Lb.elem[i]);
		//printf( "addr:%p,   value: %d\n", (a+i),a[i]);
	    //printf( "addr:%d,   value: %d\n", (a+i),a[i]);
	}

	MergeList_sq( La, Lb, Lc);
	printf("\n===========The Sq_List_c is =========\n");
	for(i=0;i <10; i++)
	printf( " addr:%p, value: %d  \n",&(Lc.elem[i]),Lc.elem[i]);

	if ( ListDelete_Sq( Lc,4,temp) == 1 )
	{
		printf("\n==========The Delete Sq_List_c is==========\n");
		for(i=0;i <9; i++)
		printf( " addr:%p, value: %d  \n",&(Lc.elem[i]),Lc.elem[i]);

		printf("the delet element is : %d\n",temp);
	}
	
	 i = LocateElem_Sq(Lc,6,compare) ;
	 printf("\nthe Locate element is the :%d\n ", i);

}



