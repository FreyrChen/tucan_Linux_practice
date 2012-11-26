//输入一串字符，只把大写字母改为小写，并且把输入的字母向后移一位。

#include <stdio.h>
#include <stdlib.h>

int main( void )
{
	int ch;
	int i;

	while( ( ch=getchar() ) != EOF )
	{
//	ch=getchar();
		if( ch>64 && ch<91 )
			ch = ch + 33;
		if( ch>96 && ch<123 )
			ch = ch + 1;
		printf("%c", ch);
	}
	//ch =99;
	//putchar( &ch );
	//printf("%c \n", ch);
	return (1);
}
