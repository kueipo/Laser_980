
#ifndef	__TASK_FEEDBACK_H
#define	__TASK_FEEDBACK_H

#include "DEV_Config.h"
#include "Task.h"

/* App Index -----------------------------------------------------------------*/
enum TASK_FB_INDEX{
	TASK_FB_SYSTEM_READY,
	TASK_FB_SET_DC24V_ADC,
	TASK_FB_SETLASERCURADC,
	TASK_FB_SETLASERPULSEWIDTH,
	
	TASK_FB_UPDATA,
	TASK_FB_PRODUCT_DATE,
	TASK_FB_VERSION,
	TASK_FB_SYSTEM_RESET,

	TASK_FB_TOTAL_QTY,
};

void Task_FB_Marks_Handler_Callback(void);
void Task_FB_Pro_Handler_Callback(void);
void Enable_Feedback(uint8_t index, uint8_t DelayState);
void App_Matching(void *buf);

#endif
