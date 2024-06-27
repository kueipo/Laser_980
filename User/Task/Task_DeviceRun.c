
/* Includes ------------------------------------------------------------------*/
#include "Task/Task_Common.h"

/* Define --------------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
typedef struct
{
	void (*TaskHook)(void);
} TaskLocal_TypeDef;

static TaskLocal_TypeDef TaskLocal[] = {
	{*APP_LaserRunning},
	{*APP_SafeGuard},
};
static volatile uint8_t TaskLocal_Total = sizeof(TaskLocal) / sizeof(TaskLocal[0]);

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  Task_SystemRun_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_SystemRun_Init(void)
{
}

/**
 * @brief  Task_SystemRun
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_SystemRun(void)
{
	static uint8_t index = 0;

	TaskLocal[index].TaskHook();
	index = (index + 1) % TaskLocal_Total;
}
