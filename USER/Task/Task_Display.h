
#ifndef __TASK_DISPLAY_H
#define __TASK_DISPLAY_H

enum DISPLAY_TASK_INDEX
{
//	HEART_BEAT = 0,
//	REFRESH_ALLDATA,
//	REFRESH_MS,
//	REFRESH_HZ,
//	REFRESH_POWER,
//	REFRESH_LASERCNT,
//	REFRESH_TIME,
	TESTTT,
};

void Task_Display_Init(void);
void Task_DisplayRun(void);
void Task_DisplayReady(enum DISPLAY_TASK_INDEX index);
	
#endif
