//寻找指数的算法
#include <stdio.h>

#define	MAX		1000
#define	TURE	1
#define	FALSE	0

int Erato( int *arry, int lenth);

int main( void )
{
	int num;
	int i;
	int arry[MAX];

	printf("=====================================================================\n");
	printf("Please input the max number of your arry : ");
	scanf("%d", &num );

	for( i=0; i<num; i++ )
		*(arry + i) = TURE;
//	arry[num] = '\0';
	Erato( arry, num );
}


int Erato( int *arry, int lenth)
{
	int j,k ;
	int len;
	int *arryp;

	arryp = arry;
	len = lenth;
	/*	
		for( j=1; j<(len/2); j++)
	 *(arry + 2 + 2 * j ) = FALSE;	//先去除2以外的偶数
	 */
//	while( *arryp != '\0' )
//	{
		for( j=1; j<(len/2); j++ )
		{
			if( *( arryp + j ) != FALSE )
				for( k=1; k<( len/(j+1) ); k++)
					*( arryp + j*k ) = FALSE;


		}

		arryp = arry;
		k = 0;
		for( j=1; j< len; j++ )	
		{
			if( *(arryp+j) == TURE )
			{
				printf(" %d ;", j);
				k++;
			}
			if ( k% 6 == 0 )	printf( "\n");
		}
		printf("\n");

	//}
}



