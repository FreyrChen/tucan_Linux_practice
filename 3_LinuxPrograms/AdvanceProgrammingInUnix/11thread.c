//**************************************************************
//11thread.c
//date:2012/5/280	athor:tusion@163.com
//NOTICE: TO strat with command :
//	 sudo gcc -g -Wall 11thread.c -o 11thread -pthread
//**************************************************************
#include <pthread.h>	// pthread_create();	pthread_self();
#include "stdio.h"

#define	THREAD_NOT_CREATE	1


int CreateNewThread( void );
void PrintInfo( void );
void * ThreadFunction( void *arg );
void PrintThreadId( const char *s );
int CreateThreadAndExit( void );
struct foo * foo_alloc( void );

pthread_t ntid;


void main( int argc, char *argv[] )
{
	char CommandNum;
	

	printf("--------------------  In AdvanceUnix Chapter11 Thread Opreation --------\n");

	while(1)
	{
		
		PrintInfo( );
		while( ( CommandNum = getc(stdin ) ) != EOF )
		{
			getc( stdin);		// get rid of enter "/n"
			switch( CommandNum )
			{
				case'1':
					CreateNewThread( );
					break;
				case'2':
					CreateThreadAndExit();
					break;
				case'0':
					printf( " select exit, goodbye\n");
					exit(1);
				default:
					printf("Input command is not valid!\n");
			}
			PrintInfo( );
		}
	
	}
}
//--------------------------------------------------------
//creat new thread to run the funtion
//-------------------------------------------------------
void PrintInfo( void )
{
	printf("--- Please input the operation: ----\n");
	printf("1.Creat a new thread\n");
	printf("2.Creat a new thread and get the exit status\n");
	printf("0.Exit\n");
}
//--------------------------------------------------------
//creat new thread to run the funtion P29
//-------------------------------------------------------
int CreateNewThread( void )
{
	int	err;

	err = pthread_create( &ntid, NULL, ThreadFunction, NULL);
	if( err != 0 )
	{
	//	printf("can't creat thread: %d \n", err);
		return THREAD_NOT_CREATE;
		//exit(THREAD_NOT_CREATE);
	}
	PrintThreadId("main thread:	");
	sleep(1);
	printf("main thread exit.\n");
	return 0;
	//exit(0);
}

//--------------------------------------------------------
//creat new thread to run the funtion
//-------------------------------------------------------
void * ThreadFunction( void *arg )
{
	printf("Enter new thread \n");
	PrintThreadId( "new thread:	");
	printf("Leave new thread. \n");
	return( (void *) 0 );
}

//--------------------------------------------------------
//-------------------------------------------------------
void PrintThreadId( const char *s )
{
	pid_t		pid;
	pthread_t	tid;
	
	pid = getpid();
	tid = pthread_self();
	printf("%s pid %u tid %u (0x%x)\n", s, (unsigned int)pid,
		(unsigned int)tid, (unsigned int) tid );
}


//--------------------------------------------------------
//creat new thread and get the exit status P292
//-------------------------------------------------------
int CreateThreadAndExit( void )
{
	int	err;
	void	*tret;
	
	err = pthread_create( &ntid, NULL, ThreadFunction, NULL);
	if( err != 0 )
	{
		printf("can't creat thread: %d \n", err);
		return THREAD_NOT_CREATE;
		//exit(THREAD_NOT_CREATE);
	}
	PrintThreadId("main thread:	");
	err = pthread_join( ntid, &tret);
	if( err != 0 )
	{
		printf("can't join the new thread: %d \n", err);
		return THREAD_NOT_CREATE;
		//exit(THREAD_NOT_CREATE);
	}
	printf(" new thread exit code %d\n", (int)tret);
	sleep(1);
	printf("main thread exit.\n");
	return 0;
	//exit(0);
}


/*
//--------------------------------------------------------
//mutil thread sysnc with threa mutex P304
//-------------------------------------------------------
int ThreadSyncWithMutex( void )
{
	#define	NHASH 29
	#define	HASH(fP)	( ((unsigned long)fp) % NHASH)


	struct foo *fh[NHASH];
	pthread_mutex_t	hashlock = PTHREAD_MUTEX_INITIALIZER;
	
	struct foo
	{
		int		f_count;	// protect by hashlock
		pthread_mutex_t	f_lock;
		struct foo	*f_next;
		int		f_id;
		//..... more stuff here......
	};	
	
	
	struct *foo foo_find( int id );
	void foo_hold( struct foo *fp );
	void foo_release( struct foo *fp );
}

//--------------------------------------------------------
//struct initial
//-------------------------------------------------------
struct foo * foo_alloc( void )
{
	struct foo	*fp;
	int		idx;
	

	if( ( fp = malloc( sizeof( struct foo ) )) != NULL;)
	{
		fp->f_count = 1;
		if( pthread_mutex_init( &fp->f_lock ) != 0 )
		{
			free(fp);
			return(NULL);
		}
		idx = HASH(fp);
		pthread_mutex_lock( &hashlock );
		fp->f_next = fh[idx];
		fh[idx] = fp;
		pthread_mutex_lock( &fp->lock );
		pthread_mutex_unlock( &hashlock );
		// comtinue initialization......
	}
	return( fp );
}
//--------------------------------------------------------
//add refernce to the mutex lock object
//-------------------------------------------------------
void foo_hold( struct foo *fp )
{
	pthread_mutex_lock( &hashlock );
	fp->count ++;
	pthread_mutex_unlock( &hashlock );
}

//--------------------------------------------------------
//find the object locked by mutex
//-------------------------------------------------------
struct *foo foo_find( int id )
{
	struct foo	fp;
	int		idx;
	
	idx = HASH( fp );
	pthread_mutex_lock( &hashlock );
	for( fp=fh(idx); fp!=NULL; fp=fp->next )
	{
		if( fp->f_id == id )
		{
			fp->f_count ++;
			break;
		}
	pthread_mutex_unlock( &hashlock );
	return( fp );
}


//--------------------------------------------------------
//release a refernce to the mutex lock object
//-------------------------------------------------------
void foo_release( struct foo *fp )
{
	struct foo	*tfp;
	int		idx;

	pthread_mutex_lock( &hashlock );
	if( -- fp->count == 0 )
	{
		idx = HASH( fp );
		tfp = fh[idx];
		if( tfp == fp )
			fh[idx] = fp->f_next;
		else
			{
				while( tftp->f_next != fp )
					tftp = tftp->next;
				tftp->f_next = fp->f_next;
			}
		pthread_mutex_unlock( &hashlock );
		pthread_mutex_destroy( &fp->f_lock );
		free( fp );
	}
	else
	{	
		pthread_mutex_unlock( &hashlock );
	}
}
*/
