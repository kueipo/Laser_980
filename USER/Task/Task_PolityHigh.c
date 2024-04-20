
#include "Task/Task_Common.h"

static void SendLaserCount(void);
static void SendTime(void);

typedef struct 
{	
	enum TASK_STATE State;
	void (*TaskHook) (void);
} TaskLocal_TypeDef;

static TaskLocal_TypeDef TaskLocal[] = 
{
	{SUSPEND, *SendLaserCount	},
	{SUSPEND, *SendTime 			},
};


volatile static uint8_t TaskLocal_Total = sizeof(TaskLocal) / sizeof(TaskLocal[0]);

void Task_PolityHigh(void)
{
	uint8_t index;
		
	for (index = 0; index < TaskLocal_Total; index++)
	{
		if( TaskLocal[index].State == READY )
		{
			TaskLocal[index].TaskHook();
			TaskLocal[index].State = SUSPEND;
		}
	}
}


/* ----------------------------------------------------------------------- */
/* ----------------------------------------------------------------------- */
static void SendLaserCount(void)
{
	uint32_t data = APP_ReadLaserCount();
	uint16_t buf[2];
	buf[0] = data >> 16;
	buf[1] = data ;
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_TARGET_LASERCOUNT_MODIFY, 2, buf);
}

static void SendTime(void)
{
	uint16_t buf[2] = {0};
	Time_Struct time = APP_ReadTime();
	buf[0] = time.ucHour + ((time.ucHour / 10) * 6);
	buf[0] <<= 8;
	buf[0] += ( time.ucMinute + ((time.ucMinute / 10) * 6) ); 
	buf[1] = time.ucSecond + ((time.ucSecond / 10) * 6);
	buf[1] <<= 8;
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_TARGET_TIME, 2, buf);
}

/**
* @brief  Enable_PHTask.
* @note   None.
* @param  index.
* @retval None.
*/
void Enable_PHTask(uint8_t index)
{
	if (index >= TaskLocal_Total)
		return;
	
	TaskLocal[index].State = READY;
}
