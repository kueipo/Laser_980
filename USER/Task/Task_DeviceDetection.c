
/* Includes ------------------------------------------------------------------*/
#include "Task.h"
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
static volatile Task_Typedef TaskLocal[] = {
/* 	State	RunTime	Period   current_operation */
/*	{READY, 100, 	100, 	(*APP_Water_Task)}, */
/*	{READY, 100, 	100, 	(*APP_Handpiece_Task)}, */
/*	{READY, 100, 	100, 	(*APP_Cooler_Task)}, */
/*	{READY, 100, 	100, 	(*APP_Pump_Task)}, */
/*	{READY, 100, 	100, 	(*APP_SafeLocker_Task)}, */
/*	{READY, 25, 	25, 	(*APP_Voltage_Task)}, */
/*	{READY, 50, 	100, 	(*APP_Mos_Task)}, */

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
