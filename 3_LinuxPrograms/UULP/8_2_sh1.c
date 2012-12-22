
/*
* this  is the file base on <understanding Unix/Linux Programing>
* based on the commander: write and tty
* useage:  write tty_name
* use tty commander get current tty terminal name,
* then use write funcution to send message to user.
* 2012-12-04 tusion@163.com
*/


#include<errno.h>	// perror();	errno,
#include<stdio.h>	// fgets( char *s, int size, FILE *stream );
#include<unistd.h>	// execvp();
#include<stdlib.h>  // malloc();


#define BUFF_SIZE 1024
#defien ARG_MAX 20

extern int errno;	//define in "/usr/include/errno.h"

void oops( char *string1, char *string2 );

void main( int argc, char *argv[] )
{
	char *com_string = "ls -l -a";
	char *arglist[3];
	char arg_num;
	char *buff[BUFF_SIZE];
	int i;	

	arg_num = 0;

	printf("\n******************************************************\n");
	printf("build a sample sh terminal, please input \n");
	printf("arg[%d]:", arg_num );
	while( fgets( buff, ,stdin ) != -1 && buff != "\n" )
	{
		arg[arg_num] = tring_to_arg( buff );
		arg_num++;
	}
	for( i=0; i<arg_num; i++ )
		printf("arg[%d]:", i );
	/*
	arglist[0] = "ls";
	arglist[1] = "-l";
	arglist[2] = 0;
	*/
	printf("test execvp() to excute another fuction \n");
	// attention! execvp()'s input parameter argv[]
	// the last parameter should argv[LENGTH-1] = 0;
	if( execvp( "ls", arglist ) == -1 )
		oops("execvp error", "excute error");
	printf("execvp is done \n" );




}

//=========================================================
// get commder arglist form input to execpv()
char * string_to_arg( *char buff )
{
	int length;
	char *arg;

	length = strlen( buff );
	buff[ length-1 ] = 0;
	if( malloc

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
