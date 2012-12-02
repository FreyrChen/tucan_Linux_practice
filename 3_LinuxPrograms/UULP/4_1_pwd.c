
/*
* 4_1_pwd.c
* this  is the file base on <understanding Unix/Linux Programing> P97
* based on the commander: pwd
* useage: pwd
* 2012-12-02 tusion@163.com
*/


#include<errno.h>	// perror();	errno,
#include<stdio.h>	// printf();
#include<stdlib.h>	// exit();
#include<string.h>  // strcpy();
#include<dirent.h>	// readdir();
#include<sys/types.h>
#include<sys/stat.h> //stat(); get the files info
#include<unistd.h>	// chdir();

extern int errno;	//define in "/usr/include/errno.h"

int oops( char *string1, char *string2 );
void path_to_inode( char *path, ino_t *p_inode );
void inode_to_dir( ino_t * p_inode );

int main( int argc, char *argv[] )
{
	
	ino_t inode;

	printf("\n******************************************************\n");
	printf(" pwd commander will print user current dir path\n");
	printf(" useage: 4_1_pwd.o \n\n" );
	
	path_to_inode( ".", &inode );
	inode_to_dir( &inode );	
	printf("\n\n");
	/*
	is_root_dir = inode_to_dir( &inode, path_name );
	while( is_root_dir != 2 )
	{
		if( chdir("..") == -1 )
			oops("can not change directory","");
		
		path_to_inode( ".", &inode );
		is_root_dir = inode_to_dir( &inode, path_name );
	}
	*/

	return 1;
}

//=========================================================
// from dir path to get inode number
// the dir path is unkonwn, so path always is "."
void path_to_inode( char *path, ino_t * p_inode )
{
	struct stat stat_buf;

	//stat_buf = NULL;
	if( path == NULL )
		oops("input dir path is null","");
	
	if( ( stat(path, &stat_buf) ) ==-1 )
		oops("can not get struct stat form dir path","");
	else
	{
	//	printf("stat  inode is %d\n", stat_buf.st_ino );
		*p_inode = stat_buf.st_ino;
	//	printf("get current dir's inode is %d\n", (int)*p_inode );
	}
}
	
//==========================================================
// from inod to get the directory's path name
// if this dir is root dir, return 2, otherwise return 1;
void inode_to_dir( ino_t * p_inode)
{
	DIR *dirp;
	struct dirent *dirent;
	ino_t current_inode, parent_inode;
	ino_t inode;
	char name[256];

	current_inode = 0; 
	parent_inode = 0;
	
	if( (dirp=opendir( ".." )) == NULL ) 
		oops("can not open dir","");
	while( ( dirent=readdir( dirp )) != NULL )
	{
		if( strcmp( dirent->d_name, "." ) == 0 )
			current_inode = dirent->d_ino;
		if( strcmp( dirent->d_name, "..") == 0)
			parent_inode = dirent->d_ino;
		if( dirent->d_ino == *p_inode )
		{
			//printf("[CAUTION!]success get current dir name:%s\n",
			//		dirent->d_name );
			strcpy(	name, dirent->d_name);
			//path_name =  dirent->d_name;
			//printf(" name= %s, path_name=%s \n", name, path_name );
		}
	}
	if( (closedir( dirp ) == -1) )
		oops("can not close dir","");

	if( current_inode != parent_inode )
	{
		if( chdir("..") == -1 )
			oops("can not change directory","");
		path_to_inode( ".", &inode );
		inode_to_dir( &inode );

	}
	printf("/%s", name );
}

/*
int inode_to_dir( ino_t * p_inode, char *path_name)
{
	DIR *dirp;
	struct dirent *dirent;
	ino_t current_inode, parent_inode;

	current_inode = 0; 
	parent_inode = 0;
	if( (dirp=opendir( ".." )) == NULL ) 
		oops("can not open dir","");
	while( ( dirent=readdir( dirp )) != NULL )
	{
		//printf("inode:%-8d, type:%2d, name:%.12s \n",
		//		(int)dirent->d_ino, dirent->d_type, dirent->d_name );
		//if( dirent->d_name == "." )
		if( strcmp( dirent->d_name, "." ) == 0 )
			current_inode = dirent->d_ino;
		//if( dirent->d_name == ".." )
		if( strcmp( dirent->d_name, "..") == 0)
			parent_inode = dirent->d_ino;
		if( dirent->d_ino == *p_inode )
			printf("[CAUTION!]success get current dir name:%s\n",
					dirent->d_name );
	}
	//printf(" inode is %d\n", (int)*p_inode );
	if( (closedir( dirp ) == -1) )
		oops("can not close dir","");

	//printf("current_inode=%d, parent_inode=%d \n",
	//		current_inode, parent_inode);
	if( current_inode == parent_inode && current_inode != 0)
		return 2;
	else
		return 1;
}
*/


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

