/**
* 15pipe.c
* use pice to communicate between processes
* tusion@163.com 2013/01/15
**/

#include <unistd.h> // pipe(); write();
#include <stdio.h>  // printf();
#include <sys/wait.h> //wait();
#include <sys/types.h> 
#include <stdlib.h>	//exit();
#include <string.h> //strlen();

#define BUFF_SIZE 128

void oops( char *string1, char *string2 );

void main( int argc, char* argv[] )
{
	int pipefd[2];
	pid_t pid;
	char buf[BUFF_SIZE];

	printf("=======================================\n");
	printf(" use pipe to communicate between process\n");
	
	if( pipe(pipefd) == -1 )
		oops("pipe","" );

	if( (pid=fork()) == -1 )
		oops( "can not fork process", "" );
	else if( pid > 0 )
	{	// parent process
		close( pipefd[0] ); //close pipe read port
		write( pipefd[1], argv[1], strlen(argv[1]) );
		close( pipefd[1] );
		wait( NULL );
		exit( EXIT_SUCCESS );
	}
	else if( pid == 0 )
	{	//child process
		close( pipefd[1] ); //close pie write port
		while( read( pipefd[0], &buf, 1 ) > 0 )
			write( STDOUT_FILENO, &buf, 1 );
		write( STDOUT_FILENO, "\n", 1 );
		close( pipefd[0] );
		_exit(EXIT_SUCCESS );
	}
}

			
//=========================================================
// error determin function
// string1: error operation,as "can not open file"...
// string2: error reason, as"No such file"
void oops( char *string1, char *string2 )
{	
	//as printf() is to write output to stdout
	//fprintf() is to write output to the given output stream
	fprintf( stderr, "Error: %s :", string1 );	
	perror( string2 );
	exit(1);
}




