
#ifndef BASE_DEFINE 
	#define TRUE	1
	#define FALSE	0
	#define OK		1
	#define ERROR	0
	#define INFEASIBLE	-1
	#define OVERFLOW	-2
	typedef int Status;		//定义自己的一种新数据类型	
	typedef int DataType;	//定义了链表中的数值类型
	#define BASE_DEFINE 
#endif

typedef struct
{	// 定义了顺序存储结构的链表结构
	ElemType	*elem;		// 存储空间基地址
	int			length;		// 当前长度
	int			listsize;	// 当前分配的存储容量
}SqList;

//=======================顺序线性表=============
// 构造一个空的线性链表，P23
Status InitList_Sq( SqList &L );
// 在顺序线性表L中的第i个位置之前插入新的元素e，P24
Status ListInsert_Sq( SqList &L, int i, ElemType e);
//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P26
void MergeList_sq( SqList La, SqList Lb, SqList &Lc );

// 在顺序线性表L中删除第i个位置的元素，并用e返回其值。P24
Status ListDelete_Sq( SqList &L, int i, ElemType &e);
// 在顺序线性表L中查找第一个与e满足compare（）的元素的位置，P26
Status LocateElem_Sq( SqList L,  ElemType e, Status( *compare )( ElemType, ElemType ));

// 比较两个数的大小
Status compare( ElemType a, ElemType b );

//====================================================================
//自己编写函数
//====================================================================
//获得链表的长度
Status ListLenth( SqList &L );



//对顺序链表各个功能函数的测试
void SqLsitTest(void);