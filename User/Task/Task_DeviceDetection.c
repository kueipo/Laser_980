
/* Includes ------------------------------------------------------------------*/
#include "Task/Task_Common.h"

/* Define --------------------------------------------------------------------*/
#define ENABLE_WATER_TASK 0
#define ENABLE_HANDPIECE_TASK 0
#define ENABLE_COOLER_TASK 0
#define ENABLE_PUMP_TASK 0
#define ENABLE_27V_TASK 0

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
static volatile Task_Typedef TaskLocal[] = {
/* 	State	RunTime	Period   current_operation */
#if ENABLE_WATER_TASK
	{READY, 102, 	100, 	(*APP_Water_Task)},
#endif /* ENABLE_WATER_TASK */

#if ENABLE_HANDPIECE_TASK	
	{READY, 102, 	100, 	(*APP_Handpiece_Task)},
#endif /* ENABLE_HANDPIECE_TASK */
	
#if ENABLE_COOLER_TASK
	{READY, 103, 	100, 	(*APP_Cooler_Task)},
#endif /* ENABLE_COOLER_TASK */
	
#if ENABLE_PUMP_TASK
	{READY, 104, 	100, 	(*APP_Pump_Task)},
#endif /* ENABLE_PUMP_TASK */
	
	{READY, 105, 	100, 	(*APP_SafeLocker_Task)},
	
#if ENABLE_27V_TASK
	{READY, 106, 	50, 	(*APP_Voltage_Task)},
#endif /* ENABLE_27V_TASK */
	
	{READY, 150, 	100, 	(*APP_Mos_Task)},
	
	{READY, 50, 	50, 	(*APP_VoltageDetection_Task)},

/*	{READY,	100,	10,		(*Water_CurentFlowSpeed)}, */
/*	{READY,	100,	10,		(*Water_Temperature)	}, */
/*	{READY,	100,	10,		(*Fan_Temperature)		}, */
/*	{READY,	100,	50,		(*Fan_CurrentSpeed)		}, */
	/* Add new task here */
};

static volatile uint8_t TaskLocal_Total = sizeof(TaskLocal) / sizeof(TaskLocal[0]);

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  Task_SysDete_Marks_Handler_Callback.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_SysDete_Marks_Handler_Callback(void)
{
	uint8_t index;

	for (index = 0; index < TaskLocal_Total; index++)
		if (TaskLocal[index].RunTime)
			TaskLocal[index].RunTime--;
}

/**
 * @brief  Task_SystemDetection.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_SystemDetection(void)
{
	static uint8_t index = 0;

	if (TaskLocal[index].RunTime == 0)
	{
		TaskLocal[index].TaskHook();
		TaskLocal[index].RunTime = TaskLocal[index].Period;
	}

	index = (index + 1) % TaskLocal_Total;
}
