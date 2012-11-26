/************************************************************************/
//数据结构第三章，有关链表存储栈的操作
//创建时间：2011/7/23
//作者：涂灿
/************************************************************************/
#include"Stack.h"
#include <stdlib.h>		//malloc函数在这个库中定义的
#include <stdio.h>		//scanf函数在这个库中定义的


typedef struct Node
{
	DataType data;
	struct Node *next;
}LStackNode,*LinkStack;



/************************************************************************/
// 构造一个链表存储的空栈，《零基础学数据结构》P112
/************************************************************************/
Status InitStack( LinkStack *top )
{
	*top=( LinkStack*) malloc(  sizeof( LinkStack ));
	if( *top == NULL) exit(OVERFLOW);	//空间分配失败
	(*top)->next = NULL;
	return OK;
}

/************************************************************************/
// 判断一个链表存储的栈是否为空，《零基础学数据结构》P112
/************************************************************************/
int StackEmpty( LinkStack top )
{
	if( top->next == NULL )
		return 1;
	else 
		return 0;
}

/************************************************************************/
// 进栈操作，将元素e插入到链栈的栈顶，《零基础学数据结构》P112
/************************************************************************/
int PushStack( LinkStack top, DataType e )
{
	LStackNode *p;

	p=( LStackNode*) malloc(  sizeof( LStackNode ));
	if( p == NULL) 
	{
		printf("内存分配失败！");
		exit(OVERFLOW);	//空间分配失败
	}
	p->data = e;
	p->next = top->next;
	top->next = p;
	return OK;
}

/************************************************************************/
// 出栈操作，链栈的栈顶元素删除并赋值给元素e，《零基础学数据结构》P113
/************************************************************************/
int PopStack( LinkStack top, DataType *e )
{
	LStackNode *p;
	p = top->next;
	if( p == NULL )
	{
		printf("栈已经是空的！");
		return 0;
	}
	top->next = p->next;
	*e = p->data;
	free( p );
	return OK;
}

/************************************************************************/
//取栈顶元素， 链栈的栈顶元素赋值给元素e，《零基础学数据结构》P113
/************************************************************************/
void GetTop( LinkStack top, DataType *e )
{
	LStackNode *p;

	p = top->next;
	if( p == NULL )
	{
		printf("栈已经是空的！");
		return 0;
	}
	*e = p->data;
	return OK;
}

/************************************************************************/
//求链栈的长度，即元素个数，《零基础学数据结构》P114
/************************************************************************/
int StackLength( LinkStack top )
{
	LStackNode *p;
	int count = 0;
	for( p = top; p->next != NULL; p= p->next )
		count++;
	return count;
}

/************************************************************************/
//销毁栈操作，将栈的元素按顺序将内存释放，《零基础学数据结构》P114
/************************************************************************/
int DestroyStack( LinkStack top )
{
	LStackNode *p,*q;

	for( p = top; p->next != NULL; p= p->next )
	{	
		q = p;
		free( q );
	}
}

