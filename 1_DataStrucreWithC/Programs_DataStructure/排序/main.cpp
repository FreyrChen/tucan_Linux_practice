//ѡ��Ҳ�ܹ����ַ���ʵ�ֶ����������

#include < stdio.h >

#define NUM 10  //������Ҫ���������Ĵ�С

void Slect ( int array[] );
void Pop( int array[] );

//static int Raw_array[NUM] = { 5,4,3,2,1,6,7,8,9,0 };
int Raw_array[NUM] = { 5,4,3,2,1,6,7,8,9,0 };

void main()
{
	int i,method,temp;

	printf("\n***************************************************************** \n\n");
	printf(" **************** ѡ����ַ���ʵ�ֶ���������� *****************\n");
	printf("\n***************************************************************** \n\n");
	printf("ԭʼ�������£� \n");
	for ( i=0; i<NUM; i++)
	{	
		if ( i%4 == 0 ) printf("\n");
		printf("	a[%2d]= %d,", i , Raw_array[i]);
	}
	do
	{
		temp = 1;
		printf("\n***************************************************************** \n");
		printf("��ѡ������ķ����� \n");
		printf("* 1.ѡ������ \n");
		printf("* 2.ð�ݷ����� \n");
		printf("* 3.�˳� \n");
		printf("������ѡ�����֣� ");
		scanf("%d", &method);
		switch ( method )
		{
			case 1: Slect( Raw_array ); break;
			case 2: Pop( Raw_array ); break;
			case 3: temp = 0; break;
			default: printf(" �����������������룡����\n");break;
		}
		//printf("\n++++++++++++�����ñ�����򷨿����� y/n ?   \n");
		//scanf("%d", &temp);
	}while( temp  );
	

}

//ʹ��ѡ������

void Slect ( int array[] )
{
	int i,j;
	int temp[NUM],mid;
	int ex_flag;	//����Ԫ�ؽ�������
	ex_flag = 0;
	//�Ȱ�Ҫ��������鸳ֵһ�ݽ���
	for (i=0; i<NUM; i++)
		temp[i] = array[i];

	for (i=0; i<NUM; i++)
		for (j=i+1; j<NUM; j++)
	{
		if ( temp[i] > temp[j]) 
		{	//���Ǻ���λ�õ�������λ
			mid = temp[i];
			temp[i] = temp[j];
			temp[j] = mid;
			ex_flag++;	//����󣬼���һ��
		}
	}
	//��ӡ���µ�����
	printf("\nʹ��ѡ�����������飺\n");
	for ( i=0; i<NUM; i++)
	{	
		if ( i%4 == 0 ) printf("\n");
		printf("	a[%2d]= %d,", i , temp[i]);
	}

	printf("\nʹ��ѡ���������齻���Ĵ������Ϊ��%d", NUM*(NUM-1));
	printf("\nʹ��ѡ���������齻���Ĵ�����%d\n\n", ex_flag);
}

//ʹ��ð�ݷ�����
// ���������������Ƚϣ�����С��������ǰ��
void Pop ( int array[] )
{
	int i,j;
	int temp[NUM],mid;
	int ex_flag;	//����Ԫ�ؽ�������
	int worst;		// �����㷨�������µ����齻������	
	ex_flag = 0;
	worst = 1;
	for (i=1; i<NUM; i++)
		worst = worst*i;

	//�Ȱ�Ҫ��������鸳ֵһ�ݽ���
	for (i=0; i<NUM; i++)
		temp[i] = array[i];

	for (i=0; i<NUM; i++)
	{
		for (j=0; j < (NUM-i); j++)
		{
			if ( temp[j] > temp[j+1]) 
			{	//���Ǻ���λ�õ�������λ
				
				mid = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = mid;
				ex_flag++;	//����󣬼���һ��
			}
		}
	}
	//��ӡ���µ�����
	printf("\n��ð�ݷ����������飺\n");
	for ( i=0; i<NUM; i++)
	{	
		if ( i%4 == 0 ) printf("\n");
		printf("	a[%2d]= %d,", i , temp[i]);
	}

	printf("\nʹ��ð�ݷ��������齻���Ĵ������Ϊ��%d", worst);
	printf("\nʹ��ð�ݷ��������齻���Ĵ�����%d\n\n", ex_flag);
}
