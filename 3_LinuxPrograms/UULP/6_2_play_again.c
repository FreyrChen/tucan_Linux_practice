/*
* 6_2_play_again.c
* based on UULP p160
* get user input commander char, and change terminator's default setting.
*/


#include<stdio.h>	// getc();
#include<unistd.h>	
#include<termios.h>	// struct termios* ;

int play_again( void );

void main( void )
{
	struct termios def_setting;
	struct termios change_setting;

	tcgetattr( STDIN_FILENO, &def_setting );
	//change terminator's input mode
	change_setting = def_setting;
	change_setting.c_lflag &= ~ICANON;	// no buffering
	change_setting.c_lflag &= ~ECHO;	// no echo
	change_setting.c_cc[VMIN] = 1;		// get 1 char at one time
		// TCSANOW	means change pccurs immediatelly
	tcsetattr( STDIN_FILENO, TCSANOW, &change_setting);

	play_again();


	tcsetattr( STDIN_FILENO, TCSANOW, &def_setting);

}

int play_again( void )
{
	char character;

	printf("play again?(y/n)\n");
	while( 1 )
	{
		character = getchar( );
		switch( character )
		{
			case'y':
			case'Y':return 0;
			case'n':
			case'N':
			case EOF:return 1;
			default:
				printf("incorrect input, please input y/n \n");
		}
	}
}
