/*
* a server use socket to communicate between processes
*/



#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <strings.h>
#include <string.h>
#include <time.h> 	//ctime();

#define NAME_LEN 256
#define PORTNUM 15000

void oops( char *string1, char *string2 );

int main( int args, char* argv[] )
{
		
	int socket_fd,socket_id;		
	struct sockaddr_in ip_addr;
	char hostname[NAME_LEN];
    struct hostent *host_tent;




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




