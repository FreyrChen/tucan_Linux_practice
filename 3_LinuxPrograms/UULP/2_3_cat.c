
/*
* 2_3_cat.c
* this  is the file base on <understanding Unix/Linux Programing> P62
* based on the commander: [cat]
* useage: cp source-file 
* open source file, read and print to screen.
* 2012-11-29 tusion@163.com
*/


#include<errno.h>	// perror();	errno,
#include<stdio.h>
#include<fcntl.h>	// open();
#include<unistd.h>	// close(); read();


//The buffer is used to temprare store data read from source file.
//The size of buffer will effect the performance of IO through out.
#define BUFFSIZE 104



extern int errno;	//define in "/usr/include/errno.h"

void oops( char *string1, char *string2 );

void main( int argc, char *argv[] )
{
	int buffer_times;	// count times used buffer read and write data
	FILE * source;
	char buf[BUFFSIZE];

	buffer_times = 1; 
	printf("\n******************************************************\n");
	printf(" cat commander will print the file to screen\n");
	printf(" useage: 2_3_cat.o source_file \n" );
	printf(" the default source file is sourcedata.dat \n");

	if( ( source = fopen( argv[1],'r' ) ) < 0 )
		oops("Cannot open", argv[1]);
	while( (fgets( buf, sizeof(buf), source ) ) != NULL )
	{
		
		//printf("%s", buf);
		fputs( buf, stdout );
		printf("\n**** buffer is %d,copy tiemes:%d ********\n", 
					BUFFSIZE,buffer_times++);
	}
	
	if( fclose( source ) == EOF  )
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
