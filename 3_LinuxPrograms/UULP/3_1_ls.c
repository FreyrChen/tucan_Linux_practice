
/*
* 3_1_ls.c
* this  is the file base on <understanding Unix/Linux Programing> P68
* based on the commander: ls
* useage: ls
* 2012-11-29 tusion@163.com
*/


#include<errno.h>	// perror();	errno,
#include<stdio.h>
#include<dirent.h>	// readdir();
#include<sys/types.h>

//The buffer is used to temprare store data read from source file.
//The size of buffer will effect the performance of IO through out.
#define BUFFSIZE 1024


/* basic directory struct define in /usr/include/bits/dirent.h */
/*
struct dirent
  {
#ifndef __USE_FILE_OFFSET64
    __ino_t d_ino;
    __off_t d_off;
#else
    __ino64_t d_ino;
    __off64_t d_off;
#endif
    unsigned short int d_reclen;
    unsigned char d_type;
    char d_name[256];		
  };

*/

extern int errno;	//define in "/usr/include/errno.h"
int my_ls( char *dir_path );
int oops( char *string1, char *string2 );

void main( int argc, char *argv[] )
{
	int temp = argc;

	printf("\n******************************************************\n");
	printf(" ls commander will lsit the directory of user folder\n");
	printf(" useage: 3_1__cp.o dir1 dir2 .... \n\n" );

	if( argc == 1 )
	{
		printf("open currernt dir: \".\"\n");
		my_ls(".");			//default open dir is current usr folder.
	}
	else
		while( argc-- > 1)
		{
			printf("\n>>>>> open dir %s \n", * ++argv );
			//printf("open dir %s \n", *argv[temp - argc +1] );
			my_ls( *argv );
		}
}

int my_ls( char *dir_path )
{
	int read_dir_times;	// count times to read directory
	DIR *usr_dir;
	struct dirent *dir_info;

	read_dir_times = 1; 
	if( ( usr_dir = opendir( dir_path ) ) == NULL )
		oops("Cannot open dir", dir_path );
	while( (dir_info = readdir( usr_dir )) != NULL )
	{
		printf("%d: %s \n", read_dir_times++, dir_info->d_name );
		
	}
	if( closedir(usr_dir) == -1 )
		oops("can not close dir","");

}
//=========================================================
// error determin function
// string1: error operation,as "can not open file"...
// string2: error reason, as"No such file"
int oops( char *string1, char *string2 )
{	
	//as printf() is to write output to stdout
	//fprintf() is to write output to the given output stream
	fprintf( stderr, "Error: %s :", string1 );
	perror( string2 );
	exit(1);
}
