/************************************************************************/
//���ݽṹ�ڶ��£��й�����Ĳ���
//2010.9.15
//���ߣ�Ϳ��
/************************************************************************/
#include <stdio.h>

#define TRUE	1
#define FALSE	0
#define OK		1
#define ERROR	0
#define INFEASIBLE	-1
#define OVERFLOW	-2
#define LIST_INIT_SIZE	100	//���Ա�洢�ռ�ĳ�ʼ��������
#define LISTINCREMENT	10	//���Ա�洢�ռ�ķ�������

typedef int Status	;//�����Լ���һ�����������ͣ�������
typedef int ElemType;	//�����������е���ֵ����

typedef struct
{	// ������˳��ṹ������ṹ
	ElemType	*elem;		// �洢�ռ����ַ
	int			length;		// ��ǰ����
	int			listsize;	// ��ǰ����Ĵ洢����
}SqList;


// ����һ���յ���������
Status InitList_Sq( SqList &L );
// ������������Lb�еĵ�����La�е�����Ԫ�ز��뵽La�У�P20
//void Union (List &La, List Lb);
//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P21
//void MergeList( List La, List Lb, List &Lc )��
// ����һ���յ���������P23
Status InitList_Sq( SqList &L );
// ��˳�����Ա�L��ɾ����i��λ�õ�Ԫ�أ�����e������ֵ��P24
Status ListDelete_Sq( SqList &L, int i, ElemType &e);
// ��˳�����Ա�L�в��ҵ�һ����e����compare������Ԫ�ص�λ�ã�P26
Status LocateElem_Sq( SqList L,  ElemType e,
					 Status( *compare )( ElemType, ElemType ));
//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P26
void MergeList_sq( SqList La, SqList Lb, SqList &Lc );

// �Ƚ��������Ĵ�С
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
// ����һ���յ���������P23
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
// ������������Lb�еĵ�����La�е�����Ԫ�ز��뵽La�У�P20
/************************************************************************/
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

/************************************************************************/
//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P21
/************************************************************************/
void MergeList( List La, List Lb, List &Lc )
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


/************************************************************************/
// ��˳�����Ա�L�еĵ�i��λ��֮ǰ�����µ�Ԫ��e��P24
/************************************************************************/
Status ListInsert_Sq( SqList &L, int i, ElemType e)
{
	ElemType p,q;
	int i;
	unsigned int newbase;

	// �ȼ�����λ�õĺϷ���
	if( !( (i>=1) && i<=( ListLength_Sq( L ) + 1 ) )
		return ERROR;
	if( L.length >= L.listsize )
	{	//  ����ǰ�洢�ռ������������ӷ���ռ�
		newbase = ( ElemType * )realloc( L.elem, 
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

/************************************************************************/
// ��˳�����Ա�L��ɾ����i��λ�õ�Ԫ�أ�����e������ֵ��P24
/************************************************************************/
Status ListDelete_Sq( SqList &L, int i, ElemType &e)
{
	int p,q;
	ElemType e;

	//�ȼ��ɾ��λ��i�ĺϷ���
	if( (i>=1) && ( i<=L.length) )
		return ERROR;
	p = &( L.elem[i-1] );		//	pΪ��ɾ��Ԫ��λ�ã�
	e = *p;						//	��ɾ��Ԫ�ص�ֵ����e
	q = L.elem + L.length - 1;	//	��βԪ�ص�λ��
	for( ++p; p<=q; ++p )		//	ɾ��Ԫ��֮���Ԫ������ǰ��
		*( p-1 ) = *p;
	--L.length;					//	����С
	return OK;
}


/************************************************************************/
// ��˳�����Ա�L�в��ҵ�һ����e����compare������Ԫ�ص�λ�ã�P26
/************************************************************************/
Status LocateElem_Sq( SqList L,  ElemType e,
					 Status( *compare )( ElemType, ElemType ))
{	//	���ҵ����򷵻�����L�е�λ�ã����򷵻�0
	int i,p;

	i = 1;			//	i�ĳ�ֵΪ��һ��Ԫ�ص�λ��
	p = L.elem;		//	p�ĳ�ֵΪ��һ��Ԫ�صĴ洢λ��
	while( i <= L.length && ( *compare )( *p++, e )
		++i;
	if( i<= L.length )
		return i;
	else return 0;
}

/************************************************************************/
//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P26
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
	//	����LA����LBʣ�µ�Ԫ��
	while( pa<= pa_last ) *pc++ = *pa++;
	while( pb<= pb_last ) *pc++ = *pb++;
}

// �Ƚ��������Ĵ�С
Status compare( ElemType a, ElemType b )
{
	if ( a >= b )	return 1;
	else	return 0;
}