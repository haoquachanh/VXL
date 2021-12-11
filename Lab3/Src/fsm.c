/*
 * clock_12LEDs.c
 *
 *  Created on: Nov 6, 2021
 *      Author: 1913228
 */

#include <fsm.h>
#include "main.h"
#include "timer.h"

// Time for Normal mode (mode 1)
#define MAX_RED		20
#define MAX_YELLOW	5
#define MAX_GREEN	15

int red=MAX_RED;
int yellow=MAX_YELLOW;
int green=MAX_GREEN;
int time=0;
int MODE=1;
int value;
//  for number tens
void display7SEG(int num)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_SET);
	switch (num)
	{
	case 0: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);
			break;
	case 1: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);
			break;
	case 2: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_6, GPIO_PIN_RESET);
			break;
	case 3: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_6, GPIO_PIN_RESET);
			break;
	case 4: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
			break;
	case 5: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
			break;
	case 6: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
			break;
	case 7: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2, GPIO_PIN_RESET);
			break;
	case 8: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
			break;
	case 9: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
			break;
	default: HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);
			break;
	}
}

int led_buffer [4] = {1, 2, 3, 4};
void update7SEG ( int index )
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
	switch ( index )
	{
		case 0:
				// Display the first 7 SEG with led_buffer [0]
				display7SEG(led_buffer[0]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
				break ;
		case 1:
				// Display the second 7 SEG with led_buffer [1]
				display7SEG(led_buffer[1]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET);
				break ;
		case 2:
				// Display the third 7 SEG with led_buffer [2]
				display7SEG(led_buffer[2]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET);
				break ;
		case 3:
				// Display the forth 7 SEG with led_buffer [3]
				display7SEG(led_buffer[3]);
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET);
				break ;
		default :
				break ;
	}
}
void mode1_disp()
{
	//led0,1 display time for lane A
	//led2,3 display time for lane B
	led_buffer[0]=time/10;
	led_buffer[1]=time%10;
	led_buffer[2]=0;
	led_buffer[3]=0;
}
void mode234_disp(int value)
{
	//led0,1 display MODE
	//led2,3 display value
	led_buffer[0]=0;
	led_buffer[1]=MODE;
	led_buffer[2]=value/10;
	led_buffer[3]=value%10;
}


int flagR=0;	// red led is lighting?
int flagY=0;	// yellow
int flagG=0;	// green
void changeColor()
{
	// no led is lighting OR led yellow is lighting ==> CHANGE TO LED RED: ON
	if (!(flagR==1 || flagY==1 || flagG==1) || (flagY=1))
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2||GPIO_PIN_3, GPIO_PIN_SET);
		time=red;
		flagR=1;
		flagY=0;
	}
	else
	{
		// led green is lighting ==> CHANGE TO LED YELLOW: ON
		if (flagG)
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1||GPIO_PIN_3, GPIO_PIN_SET);
			time=yellow;
			flagG=0;
			flagY=1;
		}
		// LED RED is ON  ==> change to GREEN led: ON
		else
		{
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1||GPIO_PIN_2, GPIO_PIN_SET);
			time=green;
			flagR=0;
			flagG=1;
		}
	}
}

void traffic_fsm()
{
	switch (MODE)
	{
	case 1:
		if (timer0_flag==1) time--;
		if (time<=0) changeColor();
		setTimer0(1000);
		break;
	case 2:
//		All single red LEDs are blinking in 2 Hz.
		setTimer0(500);
		if (timer0_flag==1) HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1||GPIO_PIN_4);
//		- Use two seven-segment LEDs to display the value.
//		- Use the other two seven-segment LEDs to display the mode.
		value=red;
		mode234_disp(value);
//		- The second button is used to increase the time duration value for the red LEDs.
//		- The value of time duration is in a range of 1 - 99.
//		- The third button is used to set the value
		break;
	case 3:
		setTimer0(500);
		if (timer0_flag==1) HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2||GPIO_PIN_5);
		value=yellow;
		mode234_disp(value);
		break;
	case 4:
		setTimer0(500);
		if (timer0_flag==1) HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3||GPIO_PIN_6);
		value=green;
		mode234_disp(value);
		break;
	default: break;
	}
}
