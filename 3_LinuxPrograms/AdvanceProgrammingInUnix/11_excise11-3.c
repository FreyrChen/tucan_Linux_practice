//******************************************************
//thsi is excise in chapter 11, question 11.1
// correct the program in list 11-3
//*****************************************************

#include <stdlib.h>
#include <pthread.h>

struct foo
{
	int a,b,c,d;
};

void printfoo( const char *s, const struct foo *fp)
{
	printf(s);
	printf(" struct at address: 0x%x\n",(unsigned) fp );
	printf(" foo.a = %d\n", fp->a);
	printf(" foo.b = %d\n", fp->b );
	printf(" foo.c = %d\n",	fp->c );
	printf(" foo.d = %d\n", fp->d );
}

void *thread_fn1( void *arg )
{
	//struct foo data = {1,2,3,4};
	struct foo *fdata;
	if( ( fdata = malloc( sizeof( struct foo ) )) == NULL )
	{
		printf(" malloc error\n");
		exit(0);
	}
	/*
	*fdata = { ->a = 1,
		   ->b = 2,
		   ->c = 3,
		   ->d = 4};
	*/
	fdata->a = 1;
	fdata->b = 2;
	fdata->c = 3;
	fdata->d = 4;
	
	printfoo( "thread1:\n", fdata );
	pthread_exit( (void*) fdata);
}

void *thread_fn2( void *arg )
{
	printf("thread2: ID is %d\n", pthread_self() );
	pthread_exit( (void*) 0 );
}

int main( void )
{
	int		error;
	pthread_t	tid1, tid2;
	struct	foo	*fp;
	
	error = pthread_create( &tid1, NULL, thread_fn1, NULL );
	if( error != 0 )
		{
			printf(" thread cread error!\n");
			exit(0);
		}
	error = pthread_join( tid1, (void *) &fp );
	if( error != 0 )
	{
		printf(" can't join the thread 1\n");
		exit(0);
	}
	sleep(1);
	
	printf(" patent starting second thread\n");
	error = pthread_create( &tid2, NULL, thread_fn2, NULL);
	if( error != 0 )
	{
		printf(" theaed 2 creat error\n");
		exit(0);
	}
	sleep(1);
		
	printfoo(" parent:\n", fp );
	
	exit(0);
}
			
		
