

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

//=================���Ա�ĵ�����洢�ṹ===================
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
} LNode,*LinkList;


//=======================��������=============
// ��λ������n��Ԫ�ص�ֵ������ͷ���ΪL�ĵ���������P30
void CreatList_L( LinkList &L, int n);
// ��������L�еĵ�i������Ԫ�ط��ظ�e��P29
Status GetElem_L( LinkList L, int i, ElemType &e);
// ��ͷ���ָ��ΪL�ĵ����������еĵ�i��λ��֮ǰ����Ԫ��e,P29
Status ListInsert_L( LinkList &L, int i,ElemType e);
// ��ͷ���ָ��ΪL�ĵ����������еĵ�i��λ�õ�Ԫ��ɾ��,���ҷ���ɾ����Ԫ��e,P30
Status ListDelet_L( LinkList &L, int i,ElemType &e);
//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P31
void MergeList_L( LinkList &La, LinkList &Lb, LinkList &Lc );

//��֪����ϵ���������ֵ���������У���������˳��ϲ�������,P21
//void MergeList( List La, List Lb, List &Lc );
// ������������Lb�еĵ�����La�е�����Ԫ�ز��뵽La�У�P20
//void Union ( List &La, List Lb);

//�����Ա�ĸ������ܺ���������
void ListTest( void );