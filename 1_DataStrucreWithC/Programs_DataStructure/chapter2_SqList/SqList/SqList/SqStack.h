
#ifndef BASE_DEFINE 
	#define TRUE	1
	#define FALSE	0
	#define OK		1
	#define ERROR	0
	#define INFEASIBLE	-1
	#define OVERFLOW	-2
	typedef int Status;
	typedef int DataType;	//�����������е���ֵ����
	#define BASE_DEFINE 
#endif

typedef int ElemType;
typedef int SElemType;

#define STACK_INIT_SIZE	100	//ջ��ʼ����ռ��С
#define STACK_INCREMENT	10	//�洢�ռ��������

typedef struct
{
	SElemType	*base;
	SElemType	*top;
	int			stacksize;
}SqStack;

// ����һ����ջ��P47
Status InitStack( SqStack &S );
//���ջ��Ԫ�أ�P47
Status GetTop( SqStack S, SElemType &e );
//�����µ�Ԫ��e��Ϊջ����P47
Status Push( SqStack &S, SElemType e);
//��ջ��Ԫ��e�Ƴ���P47
Status Pop( SqStack &S,SElemType &e );
//����ջ�ĳ��ȣ��������ѧ���ݽṹ��P105
int SqStackLength ( SqStack S );

void SqStackTest( void );