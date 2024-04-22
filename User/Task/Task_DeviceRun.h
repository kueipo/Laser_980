#ifndef __TASK_DEVICERUN_H
#define __TASK_DEVICERUN_H

#include "stdint.h"

typedef struct 
{
	uint8_t RunEnable:1; 
	uint8_t FootSwitch:1;
}OperationFlag_TypeDef;
extern OperationFlag_TypeDef OperationFlag;

void Task_SystemRun_Init(void);
void Task_SystemRun(void);
	
#endif
