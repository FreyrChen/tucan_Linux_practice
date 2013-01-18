/*
* use socket comunicate between processes
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

#define NAME_LEN 256
#define PORTNUM 13000


void oops( char *string1, char *string2 );

int main( int args, char* argv[] )
{
	
	int socket_fd,socket_id;
	struct sockaddr_in ip_addr;
	char hostname[NAME_LEN];
	struct hostent *host_tent;
	FILE * socket_fp;
	char *ctime;
	time_t now_time;

	//1.Build a socket
	socket_fd = socket( AF_INET, SOCK_STREAM, 0 );
	if( socket_fd == -1 )
		oops("can not build a socket","socket" );
	
	//2.Bind IP and prot to socket.
	bzero( &ip_addr, sizeof( ip_addr ) );
	gethostname( hostname, NAME_LEN );
	host_tent = gethostbyname( hostname );
//	printf(" addr is %s \n", host_tent->h_addr );
	strncpy( &ip_addr.sin_addr, host_tent->h_addr, host_tent->h_length );
	ip_addr.sin_port = htons( PORTNUM );
	ip_addr.sin_family = AF_INET;
	
	if( bind( socket_fd, (struct sockaddr * )&ip_addr,
		sizeof( ip_addr )) != 0 )
		oops("can not bind", "bind" );

	//3.keep listen to the port
	if( listen( socket_fd, 1 ) !=0 )
		oops( "listen","" );
	
	//4.main loop, keep service
	while(1)
	{
		socket_id = accept( socket_fd, NULL, NULL );
		printf("Wow, I have got you, can i help you?\n");
		if( socket_id == -1 )
			oops("accpt","");
		socket_fp = fdopen( socket_id, "w" );
		if( socket_fp = NULL )
			oops("socket file is not exsit", "fdopen");
		now_time = time(NULL );

		fprintf( socket_fp, "The time here is ..");
	//	fprintf( socket_fp, "%s", ctime( &now_time ) );
		fclose( socket_fp );
	
	}

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






