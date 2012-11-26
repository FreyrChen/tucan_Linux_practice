#include <stdio.h>
//guess the number

int main( void )
{
	int RealNum = 58;
	int InputNum, i,j;
	
	while( 1)
	{
		for( i=0; i<=20; i++ )
			printf("=");
		printf("\n");

		printf("Please input the number:\n");
		scanf("%d", &InputNum);

		if ( InputNum == RealNum )
			printf("Congretlations, you got it!!!\n");
		else if ( InputNum > RealNum )
			printf("Oh,you input number is greater than the real number.Try again!\n");
		else if ( InputNum < RealNum )
			printf("Oh,you input number is lower than the real number.Try again!\n");

		for ( i=0; i<=20; i++)
			printf("=");
		printf("\n");
	}
}
