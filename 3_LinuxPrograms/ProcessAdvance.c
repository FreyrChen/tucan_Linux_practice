/** 
*ProcessAdvance.c
*tusion@163.com 2012/08/26
*/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>		//open()
#include<sys/wait.h>	//wait(); waitpid();

int main( int argc, char *argv[] )
{
	FILE * data_file;
	int error_no;
	pid_t	pid;
	int 	exit_status;

	/**
	* Used the standard C libary's error output
	* every error and excetions store by gloable flag errno.
	* strerror() translate the errno number's message
	* perror() print user defined message, and out put errno message
	*/

	if( ( data_file = fopen("data.txt","r") ) == NULL );
	{
		//	fprintf( stderr, "EACCES: %s \n", strerror( EACCES ) );
		printf( "error_no=%d,( %s )\n", errno,strerror( errno ) );
		//	errno = ENOENT;
		perror( "open data file data.txt" );
	}
	printf(" is there continue to go through? \n");

	/**
	*Muti Process fork and wait function
	*/
	printf("\nMuti Process fork and wait function\n");
	if( ( pid = fork() ) < 0 )
		perror("fork new child process error!");
	else if( pid == 0 )
	{					/*child process*/
			//exit(7);
			abort();
	}
	
	if(( pid = wait( &exit_status )) <0 )
		perror("Parent process wait error");
	else
		printf("wait exit child process PID:%d, exit status:%d\n", \
				pid, exit_status );

	/**
	* test make some zombie process 
	* zombie process is the child process which exit before its parent 
	* process take its exit info. At this moment, child process is alredy 
	* exit, but paren process did not know.
	*/
	int status;
	const char command[]="ps -a -o pid,ppid,state,tty,command";

	printf("\n test make some zombie process\n"); 
	if( ( pid = fork() ) < 0 )
		perror("fork new child process error!");
	else if( pid == 0 )
	{					/*child process*/
		printf("child process already exit.\n");
		exit(1);
	}
	printf("child process pid:%d \n", pid );				
	printf(" the parent process wait for a input, " \	
			"this is delay parent process to take clean child process \n");
	system( command );
	printf("Parent process sleep for 2 second.\n");
	sleep(2);	/* sleep( second ) */
	system( command );
	printf(" wait for you input to terminate the parent process...\n " );
	getchar();
	exit( 0 );
}
