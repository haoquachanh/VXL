/*
 * Button_Input.c
 *
 *  Created on: Nov 7, 2021
 *      Author: 1913228
 */


#include <fsm.h>
#include "main.h"
#include "buttonScan.h"
#include "timer.h"

static GPIO_PinState MODE_but	=GPIO_PIN_SET;
static GPIO_PinState MODIFY 	=GPIO_PIN_SET;
static GPIO_PinState SET_but  		=GPIO_PIN_SET;

static int HoldMODE_but =0;
static int HoldMODIFY   =0;
static int HoldSET		=0;


void button_scan()
{
	//scan MENU button
	GPIO_PinState temp=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_8);
	if (temp==GPIO_PIN_RESET && MODE_but==GPIO_PIN_RESET && HoldMODE_but==0)
	{
		MODE++;
		if (MODE>4) MODE=1;
		HoldMODE_but=1;
	}
	else
	{
		if (temp==GPIO_PIN_SET && MODE_but==GPIO_PIN_RESET) HoldMODE_but=0;
	}
	MODE_but=temp;

	if (MODE!=1)
	{
		//scan MODIFY button
		temp=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_9);
		if (temp==GPIO_PIN_SET && MODIFY==GPIO_PIN_SET);
		else
		{
			if (temp==GPIO_PIN_RESET && MODIFY==GPIO_PIN_RESET && HoldMODIFY==0)
			{
				value++;
				if (value>99) value=1;
				HoldMODIFY=1;
			}
			else
			{
				if (temp==GPIO_PIN_SET && MODIFY==GPIO_PIN_RESET) HoldMODIFY=0;
			}
		}
		MODIFY=temp;


		//scan SET button
		temp=HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_10);
		if (temp==GPIO_PIN_SET && SET_but==GPIO_PIN_SET);
		else
		{
			if (temp==GPIO_PIN_RESET && SET_but==GPIO_PIN_RESET && HoldSET==0)
			{
				if (MODE==2) red=value;
				else
				{
					if(MODE==3) yellow=value;
					else green=value;
				}
				HoldSET=1;
			}
			else
			{
				if (temp==GPIO_PIN_SET && SET_but==GPIO_PIN_RESET)	HoldSET=0;
			}
		}
		SET_but=temp;
	}
}
