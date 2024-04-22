
/* Includes ------------------------------------------------------------------*/
#include "Task/Task_Common.h"
#include "app/APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define ENABLE_SEND_ERROR_INFO	0
#define ENABLE_SEND_VERSION 		1


/* Function prototypes -------------------------------------------------------*/
#if ENABLE_SEND_ERROR_INFO
static void SendErrorInfo(void);
#endif

#if ENABLE_SEND_VERSION
static void SendVersion(void);
#endif /* ENABLE_SEND_VERSION */

/* Variables -----------------------------------------------------------------*/

typedef struct
{
	void (*TaskHook)(void);
} TaskLocal_TypeDef;

static TaskLocal_TypeDef TaskLocal[] = {
#if ENABLE_SEND_ERROR_INFO
	{*SendErrorInfo},
#endif /* ENABLE_SEND_ERROR_INFO */	
#if ENABLE_SEND_VERSION
	{*SendVersion},
#endif /* ENABLE_SEND_VERSION */
};

static volatile uint8_t TaskLocal_Total = sizeof(TaskLocal) / sizeof(TaskLocal[0]);

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  Task_Heartbeat_Message.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_Heartbeat_Message(void)
{
	static uint8_t index = 0;
	/* Execute the current operation function */
	TaskLocal[index].TaskHook();
	index = (index + 1) % TaskLocal_Total;

	uint16_t version = (uint16_t)BSP_VERSION;
	Send_Data(DEV_INDEX_FAN, INDEX_TYPE_FEEDBACK, INDEX_BSP_VERSION, 1, &version);
	
#if 0 /* Indicator */
	DEV_LED_G_TOGGLE;
#endif
	
#if 0
	APP_LED_TimeProc(100);
#endif
#if 0 /* MCU internal temperature */
	Vref = AdcValue[ADC_VREF_INDEX];
	Vref = 1.2 / Vref;
	temperature = AdcValue[ADC_MCU_TEMP_INDEX];
	temperature = Vref*temperature;
	temperature = (1.43 - temperature)/0.0043 + 25;
	printf("B0=%0.2fv\tB1=%0.2fv\t%0.1f\r\n",Vref*(float)(AdcValue[0]),Vref*(float)(AdcValue[1]),temperature);
#endif
}

/**
 * @brief  SendErrorInfo.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_ERROR_INFO
static void SendErrorInfo(void)
{
	uint32_t state = Read_DeviceState();
	uint16_t buff[2] = {0};
	
	buff[0] = state >> 16;
	buff[1] = state;

	Send_Data(INDEX_TYPE_HEARTBEAT, INDEX_TARGET_HB_ERROR, 2, buff);
}
#endif

#if ENABLE_SEND_VERSION
/**
 * @brief  SendVersion.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void SendVersion(void)
{
	Enable_Feedback(TASK_FB_VERSION, 0);
}
#endif /* ENABLE_SEND_VERSION */
