
/*
* 5_1_writetotty.c
* this  is the file base on <understanding Unix/Linux Programing>
* based on the commander: write and tty
* useage:  write tty_name
* use tty commander get current tty terminal name,
* then use write funcution to send message to user.
* 2012-12-04 tusion@163.com
*/


#include<errno.h>	// perror();	errno,
#include<stdio.h>	// fets( char *s, int size, FILE *stream );
#include<fcntl.h>	// open();
#include<unistd.h>	// close(); read();
#include<stdlib.h> 	// exit();
#include<string.h>	// strlen();

#define BUFFSIZE 1024
extern int errno;	//define in "/usr/include/errno.h"

void oops( char *string1, char *string2 );

void main( int argc, char *argv[] )
{
	int buffer_times;	// count times used buffer read and write data
	int tty_fd;
	char buf[BUFFSIZE];

	buffer_times = 1; 
	printf("\n******************************************************\n");
	printf(" write commander will send messages to another terminal\n");
	printf(" use\" ls -li /dev/pts/\" to list all terminal name \n"); 
	printf(" useage: 5_1_writetotty tty_name\n\n" );

	if( ( tty_fd = open( argv[1],O_RDWR ) ) < 0 )  // O_WRONLY
		oops("Cannot open terminal", argv[1]);
	//while( (read( source_fd, buf, BUFFSIZE ) ) > 0 )
	while( (fgets( buf, BUFFSIZE, stdin ) ) != NULL )
	{
		if( (write( tty_fd, buf, strlen(buf) )) < 0 )
			oops("Cannot write data to target terminal",argv[1]);
		//printf("buffer is %d,copy tiemes:%d\n", BUFFSIZE,buffer_times++);
		
	}
	
	if( close( tty_fd ) == -1 )
		oops("can not close files", argv[1]);

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
