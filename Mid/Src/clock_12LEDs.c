/*
 * clock_12LEDs.c
 *
 *  Created on: Nov 6, 2021
 *      Author: 1913228
 */

#include "main.h"
#include "clock_12LEDs.h"
#include "timer.h"

// Count down from 12
int hour	= 12;
int minute	= 12;
int second	= 12;

void clearAllClock()
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6 |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9
						|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_SET);
}

void setNumberOnClock(int num)
{
	switch (num)
	{
		case 0:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_15, GPIO_PIN_RESET); break;
		case 1:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET); break;
		case 2:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET); break;
		case 3:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET); break;
		case 4:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET); break;
		case 5:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET); break;
		case 6:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET); break;
		case 7:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET); break;
		case 8:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET); break;
		case 9:		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET); break;
		case 10:	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_13, GPIO_PIN_RESET); break;
		case 11:	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_14, GPIO_PIN_RESET); break;
		default:	break;
	}
}

void clock_fsm()
{
	clearAllClock();
	if (MODE==0)
	{
		setNumberOnClock(12-second);
		setNumberOnClock(12-minute);
		setNumberOnClock(12-hour  );

		if (timer0_flag==1)
		{
			second--;
			if (second <= 0)
			{
				second=12;
				minute--;
				if (minute<=0)
				{
					minute=12;
					hour--;
					if (hour<=0) hour=12;
				}
			}
			setTimer0(1000);
		}
	}
	else
	{
		if (MODE==1) setNumberOnClock(12-hour);
		else setNumberOnClock(12-minute);
	}
}
