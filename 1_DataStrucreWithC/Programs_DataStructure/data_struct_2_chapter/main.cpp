/************************************************************************/
//数据结构第二章，有关链表的操作
//2010.9.15
//作者：涂灿
/************************************************************************/
#include <stdio.h>

#define TRUE	1
#define FALSE	0
#define OK		1
#define ERROR	0
#define INFEASIBLE	-1
#define OVERFLOW	-2
#define LIST_INIT_SIZE	100	//线性表存储空间的初始化分配量
#define LISTINCREMENT	10	//线性表存储空间的分配增量

typedef int Status	;//定义自己的一种新数据类型？？？？
typedef int ElemType;	//定义了链表中的数值类型

typedef struct
{	// 定义了顺序结构的链表结构
	ElemType	*elem;		// 存储空间基地址
	int			length;		// 当前长度
	int			listsize;	// 当前分配的存储容量
}SqList;


// 构造一个空的线性链表
Status InitList_Sq( SqList &L );
// 将所有在链表Lb中的但不在La中的数据元素插入到La中，P20
//void Union (List &La, List Lb);
//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P21
//void MergeList( List La, List Lb, List &Lc )；
// 构造一个空的线性链表，P23
Status InitList_Sq( SqList &L );
// 在顺序线性表L中删除第i个位置的元素，并用e返回其值。P24
Status ListDelete_Sq( SqList &L, int i, ElemType &e);
// 在顺序线性表L中查找第一个与e满足compare（）的元素的位置，P26
Status LocateElem_Sq( SqList L,  ElemType e,
					 Status( *compare )( ElemType, ElemType ));
//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P26
void MergeList_sq( SqList La, SqList Lb, SqList &Lc );

// 比较两个数的大小
Status compare( ElemType a, ElemType b );

void mian()
{
	int delet,a[5],b[5];

	SqList La,Lb,Lc;

	InitList_Sq( La );
	InitList_Sq( Lb );
	//InitList_Sq( Lc );
	a[5] = { 1,2,3,4,5};
	b[5] = { 6,7,8,9,0};
	La = a[];
	Lb.elem = b[];
	ListDelete_Sq( &Lb, 4, delet );
	printf("\n the delete is: %d \n", delet);


}

/************************************************************************/
// 构造一个空的线性链表，P23
/************************************************************************/
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
// 将所有在链表Lb中的但不在La中的数据元素插入到La中，P20
/************************************************************************/
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

/************************************************************************/
//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P21
/************************************************************************/
void MergeList( List La, List Lb, List &Lc )
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


/************************************************************************/
// 在顺序线性表L中的第i个位置之前插入新的元素e，P24
/************************************************************************/
Status ListInsert_Sq( SqList &L, int i, ElemType e)
{
	ElemType p,q;
	int i;
	unsigned int newbase;

	// 先检查插入位置的合法性
	if( !( (i>=1) && i<=( ListLength_Sq( L ) + 1 ) )
		return ERROR;
	if( L.length >= L.listsize )
	{	//  若当前存储空间已满，则增加分配空间
		newbase = ( ElemType * )realloc( L.elem, 
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

/************************************************************************/
// 在顺序线性表L中删除第i个位置的元素，并用e返回其值。P24
/************************************************************************/
Status ListDelete_Sq( SqList &L, int i, ElemType &e)
{
	int p,q;
	ElemType e;

	//先检查删除位置i的合法性
	if( (i>=1) && ( i<=L.length) )
		return ERROR;
	p = &( L.elem[i-1] );		//	p为被删除元素位置；
	e = *p;						//	被删除元素的值赋给e
	q = L.elem + L.length - 1;	//	表尾元素的位置
	for( ++p; p<=q; ++p )		//	删除元素之后的元素依次前移
		*( p-1 ) = *p;
	--L.length;					//	表长减小
	return OK;
}


/************************************************************************/
// 在顺序线性表L中查找第一个与e满足compare（）的元素的位置，P26
/************************************************************************/
Status LocateElem_Sq( SqList L,  ElemType e,
					 Status( *compare )( ElemType, ElemType ))
{	//	若找到，则返回其在L中的位置，否则返回0
	int i,p;

	i = 1;			//	i的初值为第一个元素的位序
	p = L.elem;		//	p的初值为第一个元素的存储位置
	while( i <= L.length && ( *compare )( *p++, e )
		++i;
	if( i<= L.length )
		return i;
	else return 0;
}

/************************************************************************/
//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P26
/************************************************************************/
void MergeList_sq( SqList La, SqList Lb, SqList &Lc )
{
	int pa,pb;
	int pa_last,pb_last;

	pa = La.elem;
	pb = Lb.elem;
	Lc.listsize = Lc.length = La.length + Lb.length;
	pc = Lc.elem = ( ElemType* ) malloc ( Lc.listsize*sizeof(ElemType) );
	if( !Lc.elem ) exit( OVERFLOW );
	pa_past = La.elem + La.length - 1;
	pb_past = Lb.elem + Lb.length - 1;
	while( pa <= pa_last && pb<= pb_last )
	{
		if( *pa <= *pb ) *pc++ = *pa++;
		else *pc++ = *pb++;
	}
	//	插入LA或者LB剩下的元素
	while( pa<= pa_last ) *pc++ = *pa++;
	while( pb<= pb_last ) *pc++ = *pb++;
}

// 比较两个数的大小
Status compare( ElemType a, ElemType b )
{
	if ( a >= b )	return 1;
	else	return 0;
}