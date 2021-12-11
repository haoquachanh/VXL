# include "timer.h"
int timer0_counter = 0;
int timer0_flag = 0;
int TIMER_CYCLE = 10;

// duration = 10 <=> 10ms ( duration >=10 && duration mod 10==0 )
// => For example, to have 1s => setTimer0(1000);
void setTimer0(int duration)
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

//
//void setTimerBlink()
//{
//	timerBlink_counter = 50; //500ms
//	blinkFlag=0;
//}
//
//void timerRunBlink()
//{
//	if( timerBlink_counter > 0)
//	{
//		timerBlink_counter --;
//		if( timerBlink_counter <= 0) blinkFlag=1;
//	}
//}
