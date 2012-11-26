//学习使用递归函数P138 7.11一题和二题和三题
#include <stdio.h>

int hermite( int n, int x);
void binarry_to_ascii( unsigned int value);
int gcd( unsigned int M, unsigned int N );
int ascii_to_integer( char *string );


int main( void )
{
	int i ;
	i = 469;
	 
	int n,x;
	n = 3;
	x = 2;
	
	char ascii[20]={"23132324"};



	binarry_to_ascii( i );

	i = hermite( n, x);
	printf("\n the y is :%d \n",i);

	i = gcd( 24, 16 );
	printf("\n the y is :%d \n",i);


	i=ascii_to_integer( ascii );
	printf("\n the y is :%d \n",i);
	
}

//递归调用在n=3,x=2 时，y = 40；
int hermite( int n, int x)
{
	int y;
	//y = 0;

	if( n <= 0 )
		y = 1;
	else if( n ==1 )
		y = 2 * x;
	else 
		y = 2 * x *hermite( n-1, x ) - 2 * ( n-1 ) *hermite( n-2, x );
	/*
	{
		y = 2 * x *hermite( n-1, x );
		y = y - 2 * ( n-1 ) *hermite( n-2, x );
	}
	*/
	return y;
}


//递归调用，把一个字符串或者数组，每个字符都顺序打印出来。
void binarry_to_ascii( unsigned int value)
{
	unsigned int quotient;
		
	quotient = value / 10;
	if ( quotient != 0 )
		binarry_to_ascii( quotient );
	putchar( value % 10 + '0' );

}

//递归调用，找到两个数的最大公约数
int gcd( unsigned int M, unsigned int N )
{
	int R;

	R = 0;

	if( M % N == 0 )
		return N;
	else if ( ( R = M % N ) && ( R > 0 ) )
		gcd( N, R );
	else 
		return 0;
}
//把字符串转换为数字，然后打印。
int ascii_to_integer( char *string )
{
	unsigned int integer;
	integer = 0;

	while( ( *string >= '0') && ( *string <= '9')  )
	{
		//integer += *string * 10 + *string;
		integer = integer * 10;
		integer = integer + ( *string - '0');
		string++;
	}
	if ( *string == '/0' ) 
		return 0;
	return integer;
}
