/*
* UULP P183 P187
* use curses lib to contril tty
* compile commander:
* gcc -g -Wall code.c  -o code.o  -I/usr/include -L/usr/lib -lncurses
*/

#include<stdio.h>
#include<unistd.h>
#include<curses.h>

void main( void )
{
	int i;

	initscr();
	clear();
	for( i=0; i<LINES; i++)
	{
		move( i,i+i );
		if( i%2 == 1 )
			standout();
		addstr("hello, world! ");
		if( i%2 == 1 )
			standend();
	//	sleep(1);
		refresh();
		sleep(1);
		move( i,i+i );
		addstr("              ");
	}
	//getch();
	endwin();
}
