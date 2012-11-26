//判断矩阵是不是单位矩阵？
#include <stdio.h>

#define	MAX_X	10
#define MAX_Y	10
#define	TURE	1
#define FALSE	0

bool indentity_matrix( int matrix[MAX_X][MAX_Y] );
//int indentity_matrix( int *matrix );

int main( void )
{
	unsigned int i,j;
	int mat[MAX_X][MAX_Y];
//	int mat[10][10];

	for( i=0; i<MAX_X; i++ )
		for( j=0; j<MAX_Y; j++ )
			if( j == i )
				mat[i][j] = 1;
			else mat[i][j] = 0;

			if ( indentity_matrix( mat ) )
				printf("The matrix is the I! \n");
			else
				printf("The matrix is not ... \n");
}

bool indentity_matrix( int matrix[MAX_X][MAX_Y] )
{
	unsigned int i,j;
	
	if( MAX_X != MAX_Y ) return FALSE;

	for( i=0; i<MAX_X; i++ )
		for( j=0; j<MAX_Y; j++ )
		{
			if( j == i )
			{
				if( matrix [i][j] != 1 )
					return FALSE;
			}
			else 
			{
				if ( matrix[i][j] != 0 )
					return FALSE;
			}
		}
	return TURE;
}