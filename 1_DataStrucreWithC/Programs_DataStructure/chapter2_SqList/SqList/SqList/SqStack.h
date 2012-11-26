
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

typedef int ElemType;
typedef int SElemType;

#define STACK_INIT_SIZE	100	//栈初始分配空间大小
#define STACK_INCREMENT	10	//存储空间分配增量

typedef struct
{
	SElemType	*base;
	SElemType	*top;
	int			stacksize;
}SqStack;

// 构造一个空栈，P47
Status InitStack( SqStack &S );
//获得栈顶元素，P47
Status GetTop( SqStack S, SElemType &e );
//插入新的元素e作为栈顶，P47
Status Push( SqStack &S, SElemType e);
//将栈顶元素e推出，P47
Status Pop( SqStack &S,SElemType &e );
//计算栈的长度，《零基础学数据结构》P105
int SqStackLength ( SqStack S );

void SqStackTest( void );