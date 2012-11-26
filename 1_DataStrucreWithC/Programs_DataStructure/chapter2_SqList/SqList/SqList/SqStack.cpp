/************************************************************************/
//数据结构第三章，有关顺序存储栈的操作
//创建时间：2011/7/21
//作者：涂灿
/************************************************************************/
#include"SqStack.h"
#include <stdlib.h>		//malloc函数在这个库中定义的
#include <stdio.h>		//scanf函数在这个库中定义的




/************************************************************************/
// 构造一个空栈，P47
/************************************************************************/
Status InitStack( SqStack &S)
{
	S.base =( SElemType*) malloc( STACK_INIT_SIZE * sizeof( ElemType));
	//S.base = ( SEleType* )malloc( STACK_INIT_SZIE
	if( !S.base ) exit(OVERFLOW);	//空间分配失败
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

/************************************************************************/
//获得栈顶元素，P47
/************************************************************************/
Status GetTop( SqStack S, SElemType &e )
{
	if( S.base == S.top ) return ERROR;
	e = *( S.top - 1 );
	return OK;
}



/************************************************************************/
//插入新的元素e作为栈顶，P47
/************************************************************************/
Status Push( SqStack &S, SElemType e)
{
	if( ( S.top - S.base ) >= S.stacksize )
	{
		S.base = ( ElemType *) realloc (   S.base, 
			( S.stacksize + STACK_INCREMENT ) * sizeof ( ElemType ) );
		if( ! S.base )	exit( OVERFLOW );
		S.top = S.base + S.stacksize;
		S.stacksize += STACK_INCREMENT;
	}
	*S.top++ = e;
	return OK;
}

/************************************************************************/
//将栈顶元素e推出，P47
/************************************************************************/
Status Pop( SqStack &S,SElemType &e )
{
	if( S.top == S.base )	return ERROR;
	e = *( --S.top);
	return OK;
}

/************************************************************************/
//计算栈的长度，《零基础学数据结构》P105
/************************************************************************/
int SqStackLength ( SqStack S )
{
	return ( S.top - S.base );
}



void SqStackTest( void )
{
	SqStack STest;
	int i;
	SElemType a[] = { 'a','b','c','d','e','f'};
	SElemType e;

	printf("测试栈的功能，将字符a,b,c,d,e,f分别压入栈 \n");
	InitStack( STest );
	for( i=0; i<( sizeof(a) / sizeof(a[0]) );i++ )
	{
		if(  Push( STest,a[i] ) != OK )
		{
			printf(" 入栈失败 。。。");
			return;
		}
	}

	if( GetTop( STest, e) == 1 )
		printf("the top of the stack is :%c  \n",e);
	printf("The Length of stack is %d \n ",SqStackLength (STest));
	if( Pop( STest, e) == 1 )
		printf("the stack is poped :%c  \n",e);
	if( Pop( STest, e) == 1 )
		printf("the stack is poped :%c  \n",e);
	if( GetTop( STest, e) == 1 )
		printf("Now,the top of the stack is :%c  \n",e);
	printf("The Length of stack is %d \n ",SqStackLength (STest));

	
}
