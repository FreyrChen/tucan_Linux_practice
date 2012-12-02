
/*
* 3_1_ls.c
* this  is the file base on <understanding Unix/Linux Programing> P68
* based on the commander: ls
* useage: ls
* 2012-11-29 tusion@163.com
*/


#include<errno.h>	// perror();	errno,
#include<stdio.h>	// printf();
#include<stdlib.h>	// exit();
#include<string.h>  // strcpy();
#include<dirent.h>	// readdir();
#include<sys/types.h>
#include<sys/stat.h> //stat(); get the files info
#include<pwd.h>		// getpwuid();  from stuct uid_t to get user name
#include<grp.h>
#include<time.h>	//ctime();

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
int show_file_info( struct stat *file_stat );
void st_mode_to_letters( int mode, char *info );
char * uid_to_name( uid_t uid );
char * gid_to_name( gid_t gid );

int main( int argc, char *argv[] )
{
	//int temp = argc;

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
			printf("\nopening dir \"%s\" >>>>>>\n", * ++argv );
			//printf("open dir %s \n", *argv[temp - argc +1] );
			my_ls( *argv );
		}
	return 1;
}

int my_ls( char *dir_path )
{
	//int read_dir_times;	// count times to read directory
	DIR *usr_dir;
	struct dirent *dir_info;
	// define in /usr/include/bits/dirent.h 
	//struct stat *file_stat;
	struct stat file_stat;

	//read_dir_times = 1; 
	if( ( usr_dir = opendir( dir_path ) ) == NULL )
		oops("Cannot open dir", dir_path );


	while( (dir_info = readdir( usr_dir )) != NULL )
	{
		//printf("%d:", read_dir_times++ );
		//---------------add file information ------
		if( (stat( dir_info->d_name, &file_stat )) == -1 )
			oops("can not read the information of file", dir_path);
		else
			show_file_info( &file_stat );
		
		printf(" %s \n",  dir_info->d_name );
		
	}
	if( closedir(usr_dir) == -1 )
		oops("can not close dir","");

	return 1;
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

//==========================================================
// sample print the file's information struct stat
// some data struct should transform
int show_file_info( struct stat *file_stat )
{
	char info[11];
	//char name[8];
	// struct stat defined in /usr/include/sys/stat.h
	/*
	printf("\nshow file infomation at struct stat\n");
	printf("mode:%o\n", file_stat->st_mode);
	printf("user:%d\n", file_stat->st_uid );
	*/

	st_mode_to_letters( file_stat->st_mode, info );
	printf(" %4d ", (int) file_stat->st_nlink ); // number of hard links
	printf("% -8s ", uid_to_name(file_stat->st_uid) );
	printf("% -8s ", gid_to_name(file_stat->st_gid) );
	printf("% -8ld ",(long) file_stat->st_size);
	printf("% .12s ", 4+ctime( & file_stat->st_mtime ) );
	return 1;
}

//===========================================================
// trancform data struct stat's sub-struct st_mode to human 
// readable letters.
void st_mode_to_letters( int mode, char *info )
{
	strcpy( info, "----------" );
	//printf("raw info:%s", info );

	if( S_ISDIR(mode) ) info[0] = 'd'; //directory???
	if( S_ISCHR(mode) ) info[0] = 'c'; //char device?
	if( S_ISBLK(mode) ) info[0] = 'b'; //block devices?


	if( S_IRUSR & mode ) info[1] = 'r'; //user read?
	if( S_IWUSR & mode ) info[2] = 'w';	//user write?
	if( S_IXUSR & mode ) info[3] = 'x'; //user execute?

	if( S_IRGRP & mode ) info[4] = 'r'; //group read?
	if( S_IWGRP & mode ) info[5] = 'w';	//group write?
	if( S_IXGRP & mode ) info[6] = 'x'; //group execute?

	if( S_IROTH & mode ) info[7] = 'r'; //other read?
	if( S_IWOTH & mode ) info[8] = 'w';	//other write?
	if( S_IXOTH & mode ) info[9] = 'x'; //other execute?

	printf("%s ", info );
}

//===========================================================
// trancform data struct stat's sub-struct st_uid to actual name
// based on local password file /etc/passwd.
char * uid_to_name( uid_t uid )
{
	struct passwd *passwd;	// /user/include/pwd.h
	//char *name;
	//char name[8];

	//name = malloc( 8 );	// stdlib.h
	if( ( passwd = getpwuid( uid ) ) == NULL )
		oops("uid can not match entry at passwd","");
	else
	return  passwd->pw_name ;
	//return name;
}



//===========================================================
// trancform data struct stat's sub-struct st_gid to actual name.
char * gid_to_name( gid_t gid )
{
	struct group *group;	// /user/include/grp.h
	//char *name;
	//char name[8];

	//name = malloc( 8 );	// stdlib.h
	if( ( group = getgrgid( gid ) ) == NULL )
		oops("gid can not match entry at passwd","");
	else
	{
	//	printf(" group name %8s", group->gr_name );
		return group->gr_name;
	}
}

