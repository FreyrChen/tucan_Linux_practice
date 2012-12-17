/*
* UULP  P187
* use curses lib to contril tty
* compile commander:
* gcc -g -Wall code.c  -o code.o  -I/usr/include -L/usr/lib -lncurses
*/

#include<stdio.h>
#include<unistd.h>
#include<curses.h>
#include<sys/time.h>
#include<signal.h>

#define LEFTEDGE  10
#define RIGHTEDGE 30
#define ROW       10

void move_str( void );


//right now the timer signal is not work correct.
void main( void )
{

	struct itimerval settime;
	long sec_time, usec_time;
	long usec_wait = 200100; 	//wait 2.001 s to start
	long usec_interval = 100900;	//timer interval is 1.009 s

	signal( SIGALRM, move_str );

	settime.it_value.tv_sec = usec_wait / 1000;
	settime.it_value.tv_usec = usec_wait % 1000 *1000;
	settime.it_interval.tv_sec = usec_interval / 1000;
	settime.it_interval.tv_usec = usec_interval % 1000 * 1000;

	setitimer( ITIMER_REAL, &settime, NULL);
	initscr();
	clear();

}

void move_str( void )
{
	static i=0;

	char *message = "hello";
	char *blank = "     ";
	int dir = 1;
	int pos = LEFTEDGE;
	move( ROW,pos );
	addstr( message );
	move( LINES-1, COLS-1 );
	refresh();
	//sleep(1);
	move( ROW, pos );
	addstr( blank );
	pos += dir;
	if( pos >= RIGHTEDGE )
		dir = -1;
	if( pos <= LEFTEDGE )
		dir = +1;
	
	if(i++ >10 )
		exit(0);
}
