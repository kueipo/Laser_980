
#ifndef	__TASK_FANFB_H
#define	__TASK_FANFB_H

#include "DEV_Config.h"
#include "Task.h"
	

/* App Index -----------------------------------------------------------------*/
enum TASK_FAN_INDEX{
	TASK_FAN_SYSTEM_CONTROL,
};

void Task_FAN_Marks_Handler_Callback(void);
void Task_FAN_Pro_Handler_Callback(void);
void Enable_FanFeedback(uint8_t index, uint8_t DelayState);
void Task_Fan_AppMatching(void *buf);

#endif
