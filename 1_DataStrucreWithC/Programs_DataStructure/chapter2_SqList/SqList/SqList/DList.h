#ifndef BASE_DEFINE 
	#define TRUE	1
	#define FALSE	0
	#define OK		1
	#define ERROR	0
	#define INFEASIBLE	-1
	#define OVERFLOW	-2
	typedef int Status;
	typedef int DataType;	//定义了链表中的数值类型
	#define BASE_DEFINE 
#endif


typedef struct Node
{
	struct Node *prior;
	DataType data;
	struct Node *next;
}DLinkNode,*DLinkList;

// 在双向链表初始化，若是成功返回1，否则返回0
Status InitDLinkList( DLinkList &L, int i );
// 在双向链表中位置i插入元素e，若是成功返回1，否则返回0
Status InsertDLinkList( DLinkList &L, int i, DataType e);
// 将链表的所有元素的指针都打印出来，若是成功返回1，否则返回0
Status	PrintDLinkList( DLinkList L);
// 删除双向链表中位置i元素，并通过e返回，若是成功返回1，否则返回0
Status DeleteLinkList( DLinkList &L, int i, DataType *e);
// 将双向链表L中的第i个数据元素返回给e
Status GetElem_DL( DLinkList L, int i,  DataType *e);
//对线性表的各个功能函数做测试
void DListTest();