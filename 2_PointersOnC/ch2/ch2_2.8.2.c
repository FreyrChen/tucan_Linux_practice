#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	int ch ; //输入字符
	int flag; //检测到左边括号的个数标志
	flag = 0;

	while( ( ch=getchar() ) != EOF )
	{
		if( ch = '{' ) flag += 1;

		if( flag > 0 ) 
		{
			if( ch = "}" ) flag -= 1;
		}
	}

	if( flag > 0 )
		printf("There are %d erroes!!!\n", flag );
	else 
		printf("You have passed without any erro!!!\n");
}
