/*
* to redirect the process's IO
*/


#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

void oops( char *string1, char *string2 );

void main( int args, char* argv[] )
{
	int fd;
	char buff[BUFFER_SIZE];
	pid_t pid;

	printf("========================================\n");
	printf(" redirect the process's IO \n" );
	fgets( buff, 100, stdin);
	printf("%s",buff);

	close(0);	//close stdin 
	// if closed stdin, now open a file continusely,
	// then the file discription should assgin to 0, which
	// used to be the stdin.
	fd = open("userlist.txt", 'r' );

	printf("fd=%d, now stdin is a file 'userlist.txt' \n", fd );

	fgets( buff, 100, stdin);
	printf("%s",buff);

	printf(" create a child process, and redirecte its IO\n");
	if( (pid = fork()) == -1 )
		oops("can not creat process"," fork ");
	else if( pid == 0 )
	{	// child process
		printf("child process \n");
		close(1); //close stdout
		fd = creat("userdata.txt", 666 );
		printf("fd=%d, now stdout is a file 'userdata.txt' \n", fd );
		execlp("who","who",NULL);
		perror("execlp");
		exit(1);
	}
	else if( pid>0 )
	{
		printf(" parent process \n");
		waitpid( pid, NULL, 0);
		printf("wait the child process, so exit\n");
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


