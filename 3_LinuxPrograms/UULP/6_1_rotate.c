/*
* 6_1_rotate.c
* based on UULP p154
* this is a sample to underdtand driver frame work meshnism
*/


#include<stdio.h>	// getc();
#include<ctype.h>	// islower();

void main( void )
{
	char character;

	printf(" use: ./6_1_rotate \n");
	printf(" use: stty -icanon; ./6_1_roteate-(this shut down standard pattern)\n");

	printf(" use: stty -icanon -echo; ./6_1_roteate-(this shut down standard pattern)\n");

	while( ( character = getc( stdin ) )!= EOF )
	{
		if( character == 'x' )
			character = 'a';
		else if( islower( character ) )
			character++;
		putchar( character );
	}
}

