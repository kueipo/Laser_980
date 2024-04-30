
/* Includes ------------------------------------------------------------------*/
#include "Task/Task_Common.h"

/* Define --------------------------------------------------------------------*/
#define ENABLE_PUMP_FUNCTION		0

/* Local function prototypes -------------------------------------------------*/
static void Task_SystemReady(void *arg);
static void Task_FB_SystemReady(void);

static void APP_SetDC24VADC(void *arg);
static void APP_FB_SetDC24VADC(void);

static void APP_SetLaserCurADC(void *arg);
static void APP_FB_SetLaserCurADC(void);

static void APP_SetLaserPulseWidth(void *arg);
static void APP_FB_SetLaserPulseWidth(void);

// ----------------------------------------------
static void App_Updata(void *arg);
static void Task_FB_Updata(void);

static void App_ProductDate(void *arg);
static void Task_FB_ProductDate(void);

static void App_Version(void *arg);
static void Task_FB_Version(void);

static void App_SystemReset(void *arg);
static void Task_FB_SystemReset(void);

/* Variables -----------------------------------------------------------------*/
typedef struct
{
	volatile uint8_t type;
	volatile uint8_t target;
	void (*current_operation)(void *arg);
}LOCAL_APP_TABLE;

static volatile LOCAL_APP_TABLE AppTable[] = {
	{INDEX_TYPE_OPERATE,	INDEX_SYSTEM_READY,			(*Task_SystemReady)},
	{INDEX_TYPE_OPERATE,	PROTECT_DC24_ADC,		    (*APP_SetDC24VADC)},
	{INDEX_TYPE_OPERATE,	PROTECT_CURRENT_ADC,		(*APP_SetLaserCurADC)},
	{INDEX_TYPE_OPERATE,	PROTECT_PULSEWIDTH,			(*APP_SetLaserPulseWidth)},
	
	/* Add new variables here */
	{INDEX_TYPE_OPERATE,	INDEX_TARGET_UPDATA, 		(*App_Updata)},
	{INDEX_TYPE_OPERATE,	INDEX_TARGET_PRODUCT_DATE, (*App_ProductDate)},
	{INDEX_TYPE_OPERATE,	INDEX_BSP_VERSION, 			(*App_Version)},
	{INDEX_TYPE_OPERATE,	INDEX_SYSTEMRESET, 			(*App_SystemReset)},
};
static volatile uint8_t s_ucAppQty = sizeof(AppTable) / sizeof(AppTable[0]);

static volatile Task_Typedef TaskLocal[] = {	
/* State		RunTime		Period   current_operation */
	{ SUSPEND,	0,			1,		(*Task_FB_SystemReady)},
	{ SUSPEND,	0,			1,		(*APP_FB_SetDC24VADC)},
	{ SUSPEND,	0,			1,		(*APP_FB_SetLaserCurADC)},
	{ SUSPEND,	0,			1,		(*APP_FB_SetLaserPulseWidth)},
	
	/* Add new task here */
	{ SUSPEND,	0,			1,		(*Task_FB_Updata)},
	{ SUSPEND,	0,			1,		(*Task_FB_ProductDate)},
	{ SUSPEND,	0,			1,		(*Task_FB_Version)},
	{ SUSPEND,	0,			1,		(*Task_FB_SystemReset)},
};
static volatile uint8_t TaskLocal_Total = sizeof(TaskLocal) / sizeof(TaskLocal[0]);

/* Function prototypes -------------------------------------------------------*/
/* ---------------------------------------------------------------------------*/
/**
 * @brief  Task_SystemReady.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void Task_SystemReady(void *arg)
{
	uint8_t *data = arg;
	bool tmp;

	tmp = (bool)data[OFFSET_DATA_CONTENT_START + 1];
	
	APP_SystemRunSet(tmp);
#if 1
	Enable_Feedback(TASK_FB_SYSTEM_READY, 0);
#endif
}

/**
 * @brief  Task_FB_SystemReady.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SystemReady(void)
{
	uint16_t state = (uint16_t)APP_IsSystemRun();
	
	Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_SYSTEM_READY, 1, &state);
	
	TaskLocal[TASK_FB_SYSTEM_READY].State = SUSPEND;
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  APP_SetDC24VADC.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void APP_SetDC24VADC(void *arg)
{
//	uint8_t *data = arg;
//	uint16_t th_l, th_h;
//	
//	th_l = data[OFFSET_DATA_CONTENT_START + 0];
//	th_l <<= 8;
//	th_l += data[OFFSET_DATA_CONTENT_START + 1];
//	
//	th_h = data[OFFSET_DATA_CONTENT_START + 2];
//	th_h <<= 8;
//	th_h += data[OFFSET_DATA_CONTENT_START + 3];
//	
//	APP_DC24V_WriteADC(th_l, th_h);
	
#if 1
	Enable_Feedback(TASK_FB_SET_DC24V_ADC, 0);
#endif
}

/**
 * @brief  APP_FB_SetDC24VADC.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void APP_FB_SetDC24VADC(void)
{
//	uint16_t *val;

//	val = APP_DC24V_ReadADC();

//	Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, PROTECT_DC24_ADC, 2, val);

	TaskLocal[TASK_FB_SET_DC24V_ADC].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  APP_SetLaserCurADC.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void APP_SetLaserCurADC(void *arg)
{
	uint8_t *data = arg;
	uint16_t th_h, th_l;
	
	th_l = data[OFFSET_DATA_CONTENT_START + 0];
	th_l <<= 8;
	th_l += data[OFFSET_DATA_CONTENT_START + 1];
	
	th_h = data[OFFSET_DATA_CONTENT_START + 2];
	th_h <<= 8;
	th_h += data[OFFSET_DATA_CONTENT_START + 3];
	
	APP_Laser_WriteCurThreshold(th_h, th_l);
	
#if 1
	Enable_Feedback(TASK_FB_SETLASERCURADC, 0);
#endif
}
	
/**
 * @brief  APP_FB_SetLaserCurADC.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void APP_FB_SetLaserCurADC(void)
{
	TaskLocal[TASK_FB_SETLASERCURADC].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  APP_SetLaserPulseWidth.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void APP_SetLaserPulseWidth(void *arg)
{
	uint8_t *data = arg;
	uint16_t pulsewidth;
	
	pulsewidth = data[OFFSET_DATA_CONTENT_START + 0];
	pulsewidth <<= 8;
	pulsewidth += data[OFFSET_DATA_CONTENT_START + 1];
	
	APP_Laser_WritePulseWidth(pulsewidth);
	
#if 1
	Enable_Feedback(TASK_FB_SETLASERPULSEWIDTH, 0);
#endif
}

/**
 * @brief  APP_FB_SetLaserPulseWidth.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void APP_FB_SetLaserPulseWidth(void)
{
	TaskLocal[TASK_FB_SETLASERPULSEWIDTH].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_Updata.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
/* Enable only when debugging without IAP function */
#define TEST_PIC	0

static void App_Updata(void *arg)
{
	uint8_t *data = arg;
	uint8_t buf;
	
	if ((data[OFFSET_DATA_CONTENT_START + 1] != 0xAA) && (data[OFFSET_DATA_CONTENT_START + 1] != 0xA0))
		return;
		
	if (data[OFFSET_DATA_CONTENT_START + 1] == 0xA0)
	{
	#if TEST_PIC && defined(ENABLE_FAL_SUPPORT)
		opt_area = fal_partition_find("dwn");
	#endif
		buf = DOWN_TO_FAC;
	}
	else if (data[OFFSET_DATA_CONTENT_START + 1] == 0xAA)
	{
	#if TEST_PIC && defined(ENABLE_FAL_SUPPORT)
		opt_area = fal_partition_find("fac");
	#endif
		
	#ifdef ENABLE_DOWNLOAD_FAC
		buf = DOWN_TO_FAC;
	#else
		buf = DOWN_TO_DWN;
	#endif
		
	}
	else
		return;

	cf_Config_App_Flag(buf);
}

/**
 * @brief  Task_FB_Updata.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void Task_FB_Updata(void)
{	
#if 0
	HAL_FLASH_OB_Launch();
	TaskLocal[TASK_FB_UPDATA].State = SUSPEND;
#endif
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_ProductDate.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_ProductDate(void *arg)
{
	UNUSED(arg);
	Enable_Feedback(TASK_FB_PRODUCT_DATE, 0);
}

/**
 * @brief  flash_read.
 * @note   None.
 * @param  addr.
 *		   buf.
 *		   size.
 * @retval None.
 */
#define PRODUCT_DATE_ADDR (20 * 1024 + FLASH_BASE) /* Address of production date 20K + 0x08000000 - 4 */
static size_t flash_read(uint32_t addr, uint8_t *buf, size_t size)
{
	size_t i;

	for (i = 0; i < size; i++, addr++, buf++)
		*buf = *(uint8_t *)addr;

	return size;
}

/**
 * @brief  Task_FB_ProductDate.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_ProductDate(void)
{
	uint8_t number[4] = {0};
	uint8_t temp;
	uint8_t index;
	
	flash_read(PRODUCT_DATE_ADDR - 4, number, 4);

	/* Before transferring to 16bit data transmission,
		big-endian must be adjusted, otherwise the transmission order is reversed
	*/
	for (index = 0; index < 4; index += 2)
	{
		temp = number[index];
		number[index] = number[index + 1];
		number[index + 1] = temp;
	}

	Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_TARGET_PRODUCT_DATE, 2, (uint16_t *)number);
	TaskLocal[TASK_FB_PRODUCT_DATE].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_Version.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_Version(void *arg)
{
	UNUSED(arg);
	Enable_Feedback(TASK_FB_VERSION, 0);
}

/**
 * @brief  Task_FB_PumpControl.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_Version(void)
{
#if 1
	uint16_t temp[2];
	temp[0] = (uint16_t)(BSP_VERSION >> 16);
	temp[1] = (uint16_t)(BSP_VERSION);
	
	Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_BSP_VERSION, 2, temp);
	TaskLocal[TASK_FB_VERSION].State = SUSPEND;
#else
	;
#endif
}

/* --------------------------------------------------------------------------- */
/**
 * @brief  App_SystemReset.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SystemReset(void *arg)
{
	Enable_Feedback(TASK_FB_SYSTEM_RESET, 0);
}

/**
 * @brief  Task_FB_SystemReset.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SystemReset(void)
{
	HAL_Delay(1000);
	HAL_FLASH_OB_Launch();
#if 0
	TaskLocal[TASK_FB_SYSTEM_RESET].State = SUSPEND;
#endif
}

/* --------------------------------------------------------------------------- */
/**
 * @brief  Task_FB_Marks_Handler_Callback.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_FB_Marks_Handler_Callback(void)
{
	uint8_t index;
	for (index = 0; index < TaskLocal_Total; index++)
	{
		if (TaskLocal[index].RunTime)
			TaskLocal[index].RunTime--;
	}
}

/**
 * @brief  Task_FB_Pro_Handler_Callback.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Task_FB_Pro_Handler_Callback(void)
{
	uint8_t index;
	for (index = 0; index < TaskLocal_Total; index++)
	{
		if ((TaskLocal[index].RunTime == 0) && (TaskLocal[index].State == READY))
		{
			TaskLocal[index].TaskHook();
			TaskLocal[index].RunTime = TaskLocal[index].Period;
		}
	}
}

/* --------------------------------------------------------------------------- */
/**
 * @brief		Enable_Feedback.
 * @note		None.
 * @param		index.
 *		   		DelayState.
 * @retval	None.
 */
void Enable_Feedback(uint8_t index, uint8_t DelayState)
{
	if (DelayState)
		DelayState = TaskLocal[index].Period;

	TaskLocal[index].RunTime = DelayState;
	TaskLocal[index].State = READY;
}

/* --------------------------------------------------------------------------- */
/**
 * @brief  App_Matching.
 * @note   None.
 * @param  buf.
 * @retval None.
 */
void App_Matching(void *buf)
{
	uint8_t *data = buf;
	uint8_t type = data[OFFSET_DATA_TYPE];
	uint8_t dev = data[OFFSET_DATA_TARGET_H];
	uint8_t target = data[OFFSET_DATA_TARGET_L];
	
	if (dev != DEV_INDEX_PORTECT)
		return;
	
	for (uint8_t i = 0; i < s_ucAppQty; i++)
	{
		if ((AppTable[i].type == type) && (AppTable[i].target == target))
		{
			AppTable[i].current_operation(buf);
			break;
		}
	}
}
