
/*
* 2_2_cp.c
* this  is the file base on <understanding Unix/Linux Programing>
* based on the commander: cp
* useage: cp source-file target-file
* open source file, read and write to target files.
* this is a sample version, for more information in cp command,
* please reference in the APUE charpter 3 excise projec: 3fileOP.c
* 2012-11-22 tusion@163.com
*/


#include<errno.h>	// perror();	errno,
#include<stdio.h>
#include<fcntl.h>	// open();
#include<unistd.h>	// close(); read();


//The buffer is used to temprare store data read from source file.
//The size of buffer will effect the performance of IO through out.
#define BUFFSIZE 1024

// attribute in creat();
#define COPYMODE 0644


extern int errno;	//define in "/usr/include/errno.h"

void oops( char *string1, char *string2 );

void main( int argc, char *argv[] )
{
	int buffer_times;	// count times used buffer read and write data
	int source_fd, target_fd;
	char buf[BUFFSIZE];

	buffer_times = 1; 
	printf("\n******************************************************\n");
	printf(" cp commander will copy source file to target file\n");
	printf(" useage: 2_2_cp.o source_file target_file \n" );
	printf(" the default source file is sourcedata.dat \n");
	printf(" the default target file is targetdata.dat \n");

	if( ( source_fd = open( argv[1], O_RDONLY ) ) < 0 )
		oops("Cannot open", argv[1]);
	if( ( target_fd = creat( argv[2], COPYMODE ) ) < 0 )
		oops("Cannot open", argv[2]);
	while( (read( source_fd, buf, BUFFSIZE ) ) > 0 )
	{
		if( (write( target_fd, buf, BUFFSIZE )) < 0 )
			oops("Cannot write data to target file",argv[2]);
		printf("buffer is %d,copy tiemes:%d\n", BUFFSIZE,buffer_times++);
		
	}
	
	if( close( source_fd ) == -1 || close( target_fd ) == -1 )
		oops("can not close files","");

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
