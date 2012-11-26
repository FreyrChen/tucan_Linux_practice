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


typedef struct Node
{
	struct Node *prior;
	DataType data;
	struct Node *next;
}DLinkNode,*DLinkList;

// ��˫�������ʼ�������ǳɹ�����1�����򷵻�0
Status InitDLinkList( DLinkList &L, int i );
// ��˫��������λ��i����Ԫ��e�����ǳɹ�����1�����򷵻�0
Status InsertDLinkList( DLinkList &L, int i, DataType e);
// �����������Ԫ�ص�ָ�붼��ӡ���������ǳɹ�����1�����򷵻�0
Status	PrintDLinkList( DLinkList L);
// ɾ��˫��������λ��iԪ�أ���ͨ��e���أ����ǳɹ�����1�����򷵻�0
Status DeleteLinkList( DLinkList &L, int i, DataType *e);
// ��˫������L�еĵ�i������Ԫ�ط��ظ�e
Status GetElem_DL( DLinkList L, int i,  DataType *e);
//�����Ա�ĸ������ܺ���������
void DListTest();