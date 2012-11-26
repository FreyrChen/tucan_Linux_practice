//*************************************************************************/
// 7process.c
// data:2012/05/24	athor: tusion
// tusion@163.com
//*************************************************************************/

#define	MAXGETBUF	30

#include "stdio.h"
#include <stdlib.h>	// getenv();


int GetProcessEnv( void );

int main( int argc, char *argv[] )
{
	int i;
	char CommanderNum;
	//char * ;
	
	printf("-------- In AdvanceUnix Charpter 7 Process Operation ------- \n");
	
	while(1)
	{
		printf("Please input the operation:\n");
		printf("1.Get the current process enviorment.(p157)\n");
		printf("0.Exit.\n");
		printf(">>");
		
		while( ( CommanderNum = getc( stdin ) ) != EOF )
		{
			switch( CommanderNum)
			{
				case'1':
					GetProcessEnv( );
					break;
				
				case'0':
					exit(1);
				default:
					printf("input the commander number is not valid!\n");
			}
		}
					
	}				
	/*
	// dispaly the input argvitys with comand	
	for( i=0; argv[i]!= NULL; i++ )
	//for( i=0; i<argc; i++ )
	{
		printf(" argv[%d]:%s\n", i, argv[i]);
	}
	*/
}

int GetProcessEnv( void )
{
	char	buf[MAXGETBUF];
	//char 	name[MAXGETBUF];
	char 	*name;
	int	i;
	// get process work enviorment
	printf("GetProcessENV: get the current process work envoirment\n");
	{
		printf("GetProcessEnv:input the name of evoirment, as HOME / LOGNAME, 'q' to quit \n");
		if( fscanf("%s",buf) != NULL)
		//if( fgets( buf, MAXGETBUF, stdin) != NULL )
		{	
			//name = NULL;:
			// strlen() and strncpy not include the char '/0'
			// strcpy() copy add a char '/0'  
			 //strncpy( name, buf, strlen(buf)-1 );	
			//name = malloc( strlen(buf)-1 );
			for( i=0; buf[i]=="/0"; i++)
				name[i] = buf[i];
			//sscanf( buf, "%c", name );
			if( name == "q" )
				return 1;
			else
				//P157  input getenv(): HOME / LOGNAME / PATH /SHELL
				printf("GetProcessEnv:getenv[%s]:%s\n", name, getenv( (const char *) buf ) );	
		}
		else
			printf(" input error! \n");
	}
	/*
	for( i=1; argv[i]!= NULL; i++ )	//argv[0] is the current process name
	{
		//P157  input getenv(): HOME / LOGNAME / PATH /SHELL
		printf(" getenv[%s]:%s\n", argv[i], getenv( argv[i] ) );	
	}
	*/
}

