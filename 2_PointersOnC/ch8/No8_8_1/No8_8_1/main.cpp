//对多维数组的初始化，有点没搞明白字符和数值之间的关系。
#include <stdio.h>

char  static char_value[3][4][5][6]=
								{	{ '0xf3','\n',' ','0320',},
									{},
									{ {}, {}, {},}
								};

//{ {}, {{},{'0', ' '},}, {{},{},{'0','0','A',}}, {{},{},{'0','0','0xF3',},}, {{},{},{'0','0','0',3}}, },
//{ {}, {}, {},};




int main( void )
{
	unsigned int i,j,k,l;
	
	for( i=0; i<3; i++)
		for( j=0; j<4; j++)
			for( k=0; k<5; k++)
			{
				for( l=0; l<6; l++)
					//printf("a[%d][%d][%d][%d]= %d", i,j,k,l, char_value[i][j][k][l]);
					printf("a_%d%d%d%d= %x; ", i,j,k,l, char_value[i][j][k][l]);
				printf("\n");
			}
}


