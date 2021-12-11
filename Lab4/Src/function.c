#include "main.h"
#include "function.h"

void Led1_Display()
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
};

void Led2_Display()
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
};

void Led3_Display()
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
};

void Led4_Display()
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_6);
};

void Led5_Display()
{
	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
};
