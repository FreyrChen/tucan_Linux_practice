/**
* this project is to test timer in linux,
* find timer's resolution,stablity,load of cpu.
* tusion@163.com  2013/01/09
*/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<sys/time.h>

int oops( char *string1, char *string2 );
void func( void );

void main( void )
{
	struct itimerval old_time, new_time;

	printf("***************************************************\n");
	printf(" test timer in linux system \n");

	new.it_value.tv_sec = 5; // 5second delay;
	new.it_value.tv_usec = 0;
	new.i
	if( getitimer( ITIEMR_REAL, old_time ) == 0 )
	{
		 printf(" old time is:%d", old_time.it_value->tv_sec );
	}
	 

	 signal( SIGALRM, func );
	 alarm(2);
	printf("press ctrl+c to quite\n");
	while(1);
	
}

void func( void )
{
	printf(" reached in the func \n");
}

//========================================================
int oops( char *string1, char *string2 )
{	
	//as printf() is to write output to stdout
	//fprintf() is to write output to the given output stream
	fprintf( stderr, "Error: %s ; ", string1 );
		perror( string2 );
	exit(1);
}

