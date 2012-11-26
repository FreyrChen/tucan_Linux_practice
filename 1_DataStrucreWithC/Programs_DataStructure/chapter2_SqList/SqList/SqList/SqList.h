
#ifndef BASE_DEFINE 
	#define TRUE	1
	#define FALSE	0
	#define OK		1
	#define ERROR	0
	#define INFEASIBLE	-1
	#define OVERFLOW	-2
	typedef int Status;		//�����Լ���һ������������	
	typedef int DataType;	//�����������е���ֵ����
	#define BASE_DEFINE 
#endif

typedef struct
{	// ������˳��洢�ṹ������ṹ
	ElemType	*elem;		// �洢�ռ����ַ
	int			length;		// ��ǰ����
	int			listsize;	// ��ǰ����Ĵ洢����
}SqList;

//=======================˳�����Ա�=============
// ����һ���յ���������P23
Status InitList_Sq( SqList &L );
// ��˳�����Ա�L�еĵ�i��λ��֮ǰ�����µ�Ԫ��e��P24
Status ListInsert_Sq( SqList &L, int i, ElemType e);
//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P26
void MergeList_sq( SqList La, SqList Lb, SqList &Lc );

// ��˳�����Ա�L��ɾ����i��λ�õ�Ԫ�أ�����e������ֵ��P24
Status ListDelete_Sq( SqList &L, int i, ElemType &e);
// ��˳�����Ա�L�в��ҵ�һ����e����compare������Ԫ�ص�λ�ã�P26
Status LocateElem_Sq( SqList L,  ElemType e, Status( *compare )( ElemType, ElemType ));

// �Ƚ��������Ĵ�С
Status compare( ElemType a, ElemType b );

//====================================================================
//�Լ���д����
//====================================================================
//�������ĳ���
Status ListLenth( SqList &L );



//��˳������������ܺ����Ĳ���
void SqLsitTest(void);