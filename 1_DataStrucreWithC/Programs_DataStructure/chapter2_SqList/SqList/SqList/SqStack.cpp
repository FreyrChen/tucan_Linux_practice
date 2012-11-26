/************************************************************************/
//���ݽṹ�����£��й�˳��洢ջ�Ĳ���
//����ʱ�䣺2011/7/21
//���ߣ�Ϳ��
/************************************************************************/
#include"SqStack.h"
#include <stdlib.h>		//malloc������������ж����
#include <stdio.h>		//scanf������������ж����




/************************************************************************/
// ����һ����ջ��P47
/************************************************************************/
Status InitStack( SqStack &S)
{
	S.base =( SElemType*) malloc( STACK_INIT_SIZE * sizeof( ElemType));
	//S.base = ( SEleType* )malloc( STACK_INIT_SZIE
	if( !S.base ) exit(OVERFLOW);	//�ռ����ʧ��
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

/************************************************************************/
//���ջ��Ԫ�أ�P47
/************************************************************************/
Status GetTop( SqStack S, SElemType &e )
{
	if( S.base == S.top ) return ERROR;
	e = *( S.top - 1 );
	return OK;
}



/************************************************************************/
//�����µ�Ԫ��e��Ϊջ����P47
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
//��ջ��Ԫ��e�Ƴ���P47
/************************************************************************/
Status Pop( SqStack &S,SElemType &e )
{
	if( S.top == S.base )	return ERROR;
	e = *( --S.top);
	return OK;
}

/************************************************************************/
//����ջ�ĳ��ȣ��������ѧ���ݽṹ��P105
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

	printf("����ջ�Ĺ��ܣ����ַ�a,b,c,d,e,f�ֱ�ѹ��ջ \n");
	InitStack( STest );
	for( i=0; i<( sizeof(a) / sizeof(a[0]) );i++ )
	{
		if(  Push( STest,a[i] ) != OK )
		{
			printf(" ��ջʧ�� ������");
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
