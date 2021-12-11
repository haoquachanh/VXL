/*
 * Button_Input.c
 *
 *  Created on: Nov 7, 2021
 *      Author: 1913228
 */


#include "main.h"
#include "clock_12LEDs.h"
#include "buttonScan.h"
#include "timer.h"

static GPIO_PinState MENU		=GPIO_PIN_SET;
static GPIO_PinState INC  		=GPIO_PIN_SET;
static GPIO_PinState DEC  		=GPIO_PIN_SET;

static int HoldMENU =0;
static int HoldINC  =0;
static int HoldDEC  =0;


void button_scan()
{
	//scan MENU button
	GPIO_PinState temp=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_0);
	if (temp==GPIO_PIN_RESET && MENU==GPIO_PIN_RESET && HoldMENU==0)
	{
		MODE++;
		if (MODE>2) MODE=2;
		HoldMENU=1;
	}
	else
	{
		if (temp==GPIO_PIN_SET && MENU==GPIO_PIN_RESET) HoldMENU=0;
	}
	MENU=temp;


	if (MODE!=0)
	{
		//scan INC button
		temp=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1);
		if (temp==GPIO_PIN_SET && INC==GPIO_PIN_SET);
		else
		{
			if (temp==GPIO_PIN_RESET && INC==GPIO_PIN_RESET && HoldINC==0)
			{
				if (MODE==1)
				{
					hour--;
					if (hour<=0) hour=12;
				}
				else
				{
					minute--;
					if(minute<=0) minute=12;
				}
				HoldINC=1;
			}
			else
			{
				if (temp==GPIO_PIN_SET && INC==GPIO_PIN_RESET)
				{
					setTimerReset();
					HoldINC=0;
				}
			}
		}
		INC=temp;


		//scan DEC button
		temp=HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2);
		if (temp==GPIO_PIN_SET && DEC==GPIO_PIN_SET);
		else
		{
			if (temp==GPIO_PIN_RESET && DEC==GPIO_PIN_RESET && HoldDEC==0)
			{
				if (MODE==1)
				{
					hour++;
					if (hour>=13) hour=1;
				}
				else
				{
					minute++;
					if(minute>=13) minute=1;
				}
				HoldDEC=1;
			}
			else
			{
				if (temp==GPIO_PIN_SET && DEC==GPIO_PIN_RESET)
				{
					setTimerReset();
					HoldDEC=0;
				}
			}
		}
		DEC=temp;
	}
}
