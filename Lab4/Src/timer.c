# include "main.h"
# include "scheduler.h"

void HAL_TIM_PeriodElapsedCallback ( TIM_HandleTypeDef * htim )
{
	if(htim->Instance == TIM2)
	{
		SCH_Update();
	}
}
