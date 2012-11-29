/*
* 2_1_who.c
* this  is the file base on <understanding Unix/Linux Programing>
* based on the commander: who
* open UTMP file, read and show the info.
* read the file: "/usr/include/bits/utmp.h",
* and print the logged user info
* 2012-11-21 tusion@163.com
*/

#include <stdio.h>
#include<utmp.h>	// this file include most user info
#include<fcntl.h>	// open();
#include<unistd.h>	// close(); read();

#define BUFFSIZE sizeof( struct utmp )


int show_utmp( struct utmp * buf );

void main( void )
{

	int fd;
	struct utmp buf;
	int count = 1;


	printf("\n*********************************\n");
	printf(" this will be list the commander\"who\" \n");
	
	if( ( fd = open( UTMP_FILE, O_RDONLY )) < 0)
		//UTMP_FILE is the user info structure to store.
		perror( UTMP_FILE );
	else
		printf("success open file %s \n", UTMP_FILE);
	
	while( ( read( fd, &buf, BUFFSIZE ) ) >0)
	{
		//printf(" success read the strcut of utmp\n" );
		//printf("NO.%d: ", count );
		show_utmp( &buf );

	}

	
	close( fd );

}

int show_utmp( struct utmp * buf )
{
	if( buf == NULL )
		exit(1);
	//printf("==================================\n");
	//printf("ut_type = %d ", buf-> ut_type );
	if( buf->ut_type == USER_PROCESS )
	{
		//printf("pid: %d \n", buf->utpid );
		//printf("ut_id=%s,",		buf->ut_id);
		printf("%-8.8s",	buf->ut_user); //'-' let char allin by left.
		printf("%-8.8s", 	buf->ut_line );
		//printf("ut_host=%s,", 	buf->ut_host);
		printf("%s",	ctime(&( buf->ut_time)) ) ;
		//printf("[gmtime]:%s",	gmtime(&( buf->ut_time)) ) ;
		//printf("[mktime]:%s",	mktime(&( buf->ut_time)) ) ;
		printf("\n");
	}
}
