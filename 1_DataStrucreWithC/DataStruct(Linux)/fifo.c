/**
* fifo.c
* 2013-08-13
*
**/


#include <stdio.h>
#include <stdlib.h>


struct FIFO
{
	int ** data;
	int *head, *tail;
};

// initial fifo
int InitiFifo( unsigned int size )
{
	struct *fifo  =(FIFO *) malloc( sizeof( FIFO ) );
	if ( fifo == NULL )
	{
		fprintf( stderr, "alloc memory  error!\n");
		exit(0);
	}
	fifo->data = (int *) malloc( sizeof( int ) );
	if ( fifo->data == NULL )
	{
		fprintf( stderr, "alloc memory  error!\n");
		exit(0);
	}
	fifo->head = fifo->data;
	fifo->tail = fifo->data;
	return 1;
}


//enquene
int enqueue( )
{
}


