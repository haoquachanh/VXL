# include "timer.h"

int MODE=0;
int timer0_counter = 0;
int timer0_flag = 0;
int timerReset_counter = 0;
int TIMER_CYCLE = 10;



void setTimer0 (int duration )
{
	timer0_counter = duration / TIMER_CYCLE ;
	timer0_flag = 0;
}


void timer_run ()
{
	if( timer0_counter > 0)
	{
		timer0_counter --;
		if( timer0_counter <= 0) timer0_flag = 1;
	}
}



//RESET: MODE 1,2 --> MODE 0. (after 5s no have action)
void setTimerReset()
{
	timerReset_counter = 500; //5s
}

void timer_run_Reset()
{
	if( timerReset_counter > 0)
	{
		timerReset_counter --;
		if( timerReset_counter <= 0) MODE=0;
	}
}
