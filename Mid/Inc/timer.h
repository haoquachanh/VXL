# ifndef _TIMER_H_
# define _TIMER_H_

extern int timer0_flag ;
extern int MODE;

void setTimer0 (int duration );
void timer_run ();

void setTimerReset();
void timer_run_Reset();

# endif
