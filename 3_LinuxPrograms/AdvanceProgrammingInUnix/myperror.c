#include<errno.h>

int main( int argc, char*argv[] )
{
	fprintf( stderr, "EACCES:%S\N", strerror( EACCES ) );
	errno = ENOENT;
	perror( grgv[0] );
	exit( 0 );
}

