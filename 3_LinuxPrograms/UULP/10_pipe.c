/*
* use pipe to communitate between process
* tusion@163.com	2013/01/19
*/


#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

void oops( char *string1, char *string2 );

void main( int args, char *argc[] )
{
	int pipefd[2];
	pid_t pid;
	char buf[BUFFER_SIZE];

	printf("============================================\n");
	printf(" creat pipe to communicate between process\n");
	printf(" useage: ./10_pipe.o ls sort \n" );

	if( args < 3 )
		oops(" useage: ./10_pipe.o ls sort","" );

	if( pipe( pipefd ) == -1 )
		oops("can not creat pipe", "pipe");

	if( ( pid = fork() ) == -1 )
		oops("can not creat child process", "fork");
	else if( pid == 0 )
	{ //child process
		printf("child process,input a message:\n");
		close( pipefd[0] );
		if( fgets( buf, BUFFER_SIZE, stdin ) == NULL )
			oops("get input message error\n",  "fgets" );
		printf("child process send the message to paren process\n");
		write( pipefd[1], buf, BUFFER_SIZE );

		if( dup2( pipefd[1], 1 ) == -1)
			oops("child process can not copy pipe to stdout","dup2");
		if( close( pipefd[1]) == -1 )
			oops("child process close pipe error", "close");
		if( execlp(argc[1], argc[1], NULL ) == -1 );
			oops("child process can not exe commander", "execlp" );
	}
	else if( pid > 0 )
	{	//parent process
		printf("parent process,wait for child process\n");
		close( pipefd[1] );
		waitpid( pid, NULL, 0 );	//wait for child process
		//	if( fgets( buf, BUFFER_SIZE, pipefd[0] ) == NULL )
		//		oops(" paren gets pipe input error", "fgets" );
		if( read( pipefd[0], buf, BUFFER_SIZE ) < 0 )
			oops(" paren read pipe error\n", "read");
		printf("parent get message form child:%s\n", buf );

		if( dup2( pipefd[0], 0 ) == -1)
			oops("parent process can not copy pipe to stdout","dup2");
		if( close( pipefd[0] )== -1 )
			oops("parent process close pipe error", "close");
		if( execlp(argc[2], argc[2], NULL ) == -1 );
			oops("parent process can not exe commander", "execlp" );

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


