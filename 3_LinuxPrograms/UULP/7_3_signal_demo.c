/*
* 7_3_signal_demo.c
* this is a demo to test signal in linux is not always work well
* UUPL P200
*/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>

#define INPUT_LENGTH 100

void inthandler( int s );
void quithandler( int s );
int oops( char *string1, char *string2 );


void main( void )
{
	int nchar;
	char buf[INPUT_LENGTH];

	signal( SIGINT, inthandler );
	signal( SIGQUIT, quithandler );
	do
	{
		printf("input a message \n");
		nchar = read( STDIN_FILENO, buf, INPUT_LENGTH - 1 );
		if( nchar == -1 )
			oops(" read error", NULL );
		else
		{
			buf[nchar] = '\0';
			printf("you typed:%s", buf );
		}
	}while( strncmp( buf, "quit",4 ) != 0 );
}

void inthandler( int s )
{
	printf("received signal %d.. waiting\n", s);
	sleep(2);
	printf("Leaving inthandler \n");
}


void quithandler( int s )
{
	printf("received signal %d.. waiting\n", s );
	sleep( 2 );
	printf(" leaving quithandler \n");
}

//=========================================================
// error determin function
// string1: error operation,as "can not open file"...
// string2: error reason, as"No such file"
int oops( char *string1, char *string2 )
{	
	//as printf() is to write output to stdout
	//fprintf() is to write output to the given output stream
	fprintf( stderr, "Error: %s ; ", string1 );
	perror( string2 );
	exit(1);
}

