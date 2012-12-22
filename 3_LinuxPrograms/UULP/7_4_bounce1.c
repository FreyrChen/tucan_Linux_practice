/*
* a ball game based on UULP P214
* practice process's signal and termianl GUI
* tusion@163.com	2012/12/18
*/

#include<curses.h>
#include<signal.h>

struct ppball the_ball;

void set_up();
void wrap_up();

int main()
{
	int c;

	set_up();

	while( (c = getchar() ) != 'Q';
	{
		if( c == 'f' ) the_ball.x_ttm--;
		else if( c == 's' ) the_ball.x_ttm++;
		else if( c == 'F' ) the_ball.x_ttm--;
		else if( c == 'S' ) the_ball.x_ttm++;
	}
	
	wrap_up();

}
 

//==============================================================
//inital struct and setup
void set_up()
{
	void ball_move(int );

	the_ball.y_pos = Y_INIT;
	the_ball.x_pos = X_INIT;
	the_ball.y_ttg = the_ball.y_ttm = Y_TTM;
	the_ball.x_ttg = the_ball.x_ttm = X_TTM;
	the_ball.y_dir = 1;
	thr_ball.x_dir = 1;
	the_ball.symbol = DEL_SYMBOL;

	initscr();
	noecho();
	crmode();

	signal(SIGALRM, ball_move );
	mvaddch( the_ball.y_pos, the_ball.x_pos, the_ball.symbol );
	refresh();

	signal( SIGALRM, ball_move );
	set_ticker( 1000 / TICK_PER_SEC );
}
	set_ticker()
}
