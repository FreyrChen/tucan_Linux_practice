/*
*	6_3_signal_demo.c
* 	UULP P172 P170
* 	demo use signal() to change the SIGINT's action behavior;
* 	[Ctr]+c can not stop current process.
*/
#include<stdio.h>	//printf();
#include<unistd.h>	//sleep( int second );
#include<signal.h>

void int_func( void );

void main()
{
	int i;

	printf("================================================\n");
	printf("use signal change [Ctr]+c fucntion,try...\n");

	printf("now,change SIGINT's action is printf a message.\n");
	signal(SIGINT, int_func );
	for( i=0; i<10; i++ )
	{
		printf("%d hello\n", i);
		sleep(1);
	}

	printf("now,change SIGINT's action is just ignor, and do nothing\n");
	signal(SIGINT, SIG_IGN );
	for( i=0; i<10; i++ )
	{
		printf("%d hello\n", i);
		sleep(1);
	}
}

void int_func( void )
{
	printf("you input [Ctr]+c,but we cannot stop.\n");
}
