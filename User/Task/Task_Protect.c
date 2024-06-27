
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
	{*APP_Protect_RefreshCurrent},
	{*APP_Protect_RefreshPulseWidth},
};
static volatile uint8_t TaskLocal_Total = sizeof(TaskLocal) / sizeof(TaskLocal[0]);

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  Task_Protect_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_Protect_Init(void)
{
}

/**
 * @brief  Task_Protect
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_Protect(void)
{
	static uint8_t index = 0;

	TaskLocal[index].TaskHook();
	index = (index + 1) % TaskLocal_Total;

	APP_Protect_WDG_Callback(500);
}
