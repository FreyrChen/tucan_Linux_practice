

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

//=================线性表的单链表存储结构===================
typedef struct LNode
{
	ElemType data;
	struct LNode *next;
} LNode,*LinkList;


//=======================线性链表=============
// 逆位序输入n个元素的值，建立头结点为L的但线性链表，P30
void CreatList_L( LinkList &L, int n);
// 将单链表L中的第i个数据元素返回给e，P29
Status GetElem_L( LinkList L, int i, ElemType &e);
// 将头结点指针为L的单线性链表中的第i个位置之前插入元素e,P29
Status ListInsert_L( LinkList &L, int i,ElemType e);
// 将头结点指针为L的单线性链表中的第i个位置的元素删除,并且返回删除的元素e,P30
Status ListDelet_L( LinkList &L, int i,ElemType &e);
//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P31
void MergeList_L( LinkList &La, LinkList &Lb, LinkList &Lc );

//已知两个系线性链表的值按递增排列，按递增的顺序合并两链表,P21
//void MergeList( List La, List Lb, List &Lc );
// 将所有在链表Lb中的但不在La中的数据元素插入到La中，P20
//void Union ( List &La, List Lb);

//对线性表的各个功能函数做测试
void ListTest( void );