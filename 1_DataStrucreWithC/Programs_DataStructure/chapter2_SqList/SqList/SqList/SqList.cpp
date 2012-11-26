
/************************************************************************/
//数据结构第二章，有关顺序链表的操作
//创建时间：2011/7/03
//作者：涂灿
/************************************************************************/
//=======================顺序线性表=============

#include"SqList.h"
#include <stdlib.h> //malloc函数在这个库中定义的
#include <stdio.h>		//printf函数在这个库中定义的
/************************************************************************/
// 构造一个空的线性链表，P23
/************************************************************************/
#define LIST_INIT_SIZE	100	//线性表存储空间的初始化分配量
#define LISTINCREMENT	10	//线性表存储空间的分配增量

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
// 在顺序线性表L中的第i个位置之前插入新的元素e，P24
/************************************************************************/
Status ListInsert_Sq( SqList &L, int i, ElemType e)
{
	ElemType *p;
	ElemType *q;
    ElemType *newbase;

	// 先检查插入位置的合法性
	if( !( (i>=1) && i<=( L.length + 1 ) ))
		return ERROR;
	if( L.length >= L.listsize )
	{	//  若当前存储空间已满，则增加分配空间
		//不能在原来链表的后面增加，有可能后面的地址已经被占用
		//需要在新的内存区域划分出能存下所有链表的空间
		newbase = ( ElemType *)realloc( L.elem, 
							(L.listsize + LISTINCREMENT) * sizeof( ElemType ) );
		if( !newbase)			//	若存储分配失败
			exit( OVERFLOW );
		L.elem = newbase;		//新基地址
		L.listsize += LISTINCREMENT;	// 增加存储容量
	}
	q = &( L.elem[i-1]);		// q为插入位置
	for( p = &( L.elem[L.length - 1] ); p >= q; --p )
		*(p+1) = *p;		// 插入位置之后的元素往后移动
	*q = e;					//插入新元素e
	++L.length;				//	表长递增
	return OK;
}

Status ListLenth( SqList &L )
{
	return L.length;
}


/************************************************************************/
//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P26
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
	//	插入LA或者LB剩下的元素
	while( pa<= pa_last ) *pc++ = *pa++;
	while( pb<= pb_last ) *pc++ = *pb++;
}



/************************************************************************/
// 在顺序线性表L中删除第i个位置的元素，并用e返回其值。P24
/************************************************************************/
Status ListDelete_Sq( SqList &L, int i, ElemType &e)
{
	 ElemType *p;
	 ElemType *q;


	//先检查删除位置i的合法性
	if( (i>=1) && ( i<=L.length) )
	{	
		p = &( L.elem[i-1] );		//	p为被删除元素位置；
		e = *p;						//	被删除元素的值赋给e
		q = L.elem + L.length - 1;	//	表尾元素的位置
		for( ++p; p<=q; ++p )		//	删除元素之后的元素依次前移
			*( p-1 ) = *p;
		--L.length;					//	表长减小
		return OK;
	}
	else
	return ERROR;
}


// 比较两个数的大小
Status compare( ElemType a, ElemType b )
{
	if ( a >= b )	return 0;
	else	return 1;
}


/************************************************************************/
// 在顺序线性表L中查找第一个与e满足compare（）的元素的位置，P26
/************************************************************************/
Status LocateElem_Sq( SqList L,  ElemType e,
					 Status( *compare )( ElemType, ElemType ))
{	//	若找到，则返回其在L中的位置，否则返回0
	ElemType  i;
	ElemType *p;

	i = 1;			//	i的初值为第一个元素的位序
	p = L.elem;		//	p的初值为第一个元素的存储位置
	while( i <= L.length && ( *compare )( *p++, e ))
		++i;
	if( i<= L.length )
		return i;
	else return 0;
}


//对顺序链表各个功能函数的测试
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



