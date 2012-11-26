//选择也能够各种方法实现对数组的排序

#include < stdio.h >

#define NUM 10  //定义需要排序的数组的大小

void Slect ( int array[] );
void Pop( int array[] );

//static int Raw_array[NUM] = { 5,4,3,2,1,6,7,8,9,0 };
int Raw_array[NUM] = { 5,4,3,2,1,6,7,8,9,0 };

void main()
{
	int i,method,temp;

	printf("\n***************************************************************** \n\n");
	printf(" **************** 选择各种方法实现对数组的排序 *****************\n");
	printf("\n***************************************************************** \n\n");
	printf("原始数据如下： \n");
	for ( i=0; i<NUM; i++)
	{	
		if ( i%4 == 0 ) printf("\n");
		printf("	a[%2d]= %d,", i , Raw_array[i]);
	}
	do
	{
		temp = 1;
		printf("\n***************************************************************** \n");
		printf("请选择排序的方法： \n");
		printf("* 1.选择法排序 \n");
		printf("* 2.冒泡法排序 \n");
		printf("* 3.退出 \n");
		printf("请输入选择数字： ");
		scanf("%d", &method);
		switch ( method )
		{
			case 1: Slect( Raw_array ); break;
			case 2: Pop( Raw_array ); break;
			case 3: temp = 0; break;
			default: printf(" 输入有误，请重新输入！！！\n");break;
		}
		//printf("\n++++++++++++继续用别的排序法看看？ y/n ?   \n");
		//scanf("%d", &temp);
	}while( temp  );
	

}

//使用选择法排序

void Slect ( int array[] )
{
	int i,j;
	int temp[NUM],mid;
	int ex_flag;	//数组元素交换次数
	ex_flag = 0;
	//先把要处理的数组赋值一份进来
	for (i=0; i<NUM; i++)
		temp[i] = array[i];

	for (i=0; i<NUM; i++)
		for (j=i+1; j<NUM; j++)
	{
		if ( temp[i] > temp[j]) 
		{	//若是后面位置的数大，则换位
			mid = temp[i];
			temp[i] = temp[j];
			temp[j] = mid;
			ex_flag++;	//换序后，计数一次
		}
	}
	//打印出新的数组
	printf("\n使用选择法排序后的数组：\n");
	for ( i=0; i<NUM; i++)
	{	
		if ( i%4 == 0 ) printf("\n");
		printf("	a[%2d]= %d,", i , temp[i]);
	}

	printf("\n使用选择发排序，数组交换的次数最多为：%d", NUM*(NUM-1));
	printf("\n使用选择发排序，数组交换的次数：%d\n\n", ex_flag);
}

//使用冒泡发排序
// 将相邻两个数做比较，将较小的数换到前面
void Pop ( int array[] )
{
	int i,j;
	int temp[NUM],mid;
	int ex_flag;	//数组元素交换次数
	int worst;		// 此种算法的最坏情况下的数组交换次数	
	ex_flag = 0;
	worst = 1;
	for (i=1; i<NUM; i++)
		worst = worst*i;

	//先把要处理的数组赋值一份进来
	for (i=0; i<NUM; i++)
		temp[i] = array[i];

	for (i=0; i<NUM; i++)
	{
		for (j=0; j < (NUM-i); j++)
		{
			if ( temp[j] > temp[j+1]) 
			{	//若是后面位置的数大，则换位
				
				mid = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = mid;
				ex_flag++;	//换序后，计数一次
			}
		}
	}
	//打印出新的数组
	printf("\n用冒泡法排序后的数组：\n");
	for ( i=0; i<NUM; i++)
	{	
		if ( i%4 == 0 ) printf("\n");
		printf("	a[%2d]= %d,", i , temp[i]);
	}

	printf("\n使用冒泡发排序，数组交换的次数最多为：%d", worst);
	printf("\n使用冒泡发排序，数组交换的次数：%d\n\n", ex_flag);
}
