/*
 * clock_12LEDs.h
 *
 *  Created on: Nov 6, 2021
 *      Author: 1913228
 */

#ifndef INC_CLOCK_12LEDS_H_
#define INC_CLOCK_12LEDS_H_

extern	int hour;
extern	int minute;

void setNumberOnClock(int num);
void clearNumberOnClock(int num);
void clock_fsm();

#endif /* INC_CLOCK_12LEDS_H_ */
