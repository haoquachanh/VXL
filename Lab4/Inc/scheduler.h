#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include "main.h"

void SCH_Update( void );
uint32_t SCH_Add_Task(
		void ( *pFunction) () , unsigned int DELAY,
		unsigned int PERIOD);
void SCH_Dispatch_Tasks( UART_HandleTypeDef *huart1 );
uint8_t SCH_Delete_Task(uint8_t taskID);

void SCH_Init ( void );
void System_Initialization(void);

void setNumberonBuffer(int tid, int tick);

#endif
