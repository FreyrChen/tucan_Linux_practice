//实现矩阵乘法运算
//多维数组最为函数参数调用问题，还没搞清楚。
#include <stdio.h>

#define DIM_X 3
#define DIM_Y 2
#define DIM_Z 4

void matrix_multiply( int *m1, int *m2, int *r,int x, int y, int z );

int x[DIM_X][DIM_Y] ={ {2,-6}, {3,5}, {1,-1} };
int y[DIM_Y][DIM_Z] ={ {4,-2,-4,-5}, {-7,-3,6,7} };

int test[12][13];
int main( void )
{
	int z[DIM_X][DIM_Z];
	int i,j;
	//int *xp,*yp,*zp;
	//xp = &test; //[0][0];
	//yp = y;
	//zp = z;

		
	//matrix_multiply( x[DIM_X][DIM_Y],y[DIM_Y][DIM_Z],z[DIM_X][DIM_Z],DIM_X,DIM_Y,DIM_Z);
	//matrix_multiply( xp,yp,zp,DIM_X,DIM_Y,DIM_Z);
	matrix_multiply( &x[0][0],&y[0][0],&z[0][0],DIM_X,DIM_Y,DIM_Z);
		
	for( i=0; i<DIM_X; i++ )
	{
		for( j=0; j<DIM_Z; j++)
			printf(" %4d ; ",z[i][j] );
		printf( "\n");
	}
}

void matrix_multiply( int *m1, int *m2, int *r,
					 int x, int y, int z )
{
	int i,j,k;
	int temp;
	
	for( i=0; i<x; i++ )
	{
		for( j=0; j<z; j++)
		{
			temp = 0;
			for( k=0; k<y; k++)
			{
				//temp = temp + m1[i][k]*m2[k][j];
				temp = temp + ( *(m1+i*y+k ) ) * ( *(m2+k*z+j) );
			}
			//r[i][j] = temp;
			*( r+i*z+j )= temp;
		}
			
	}
}