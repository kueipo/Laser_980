
/* Includes ------------------------------------------------------------------*/
#include "Task/Task_Common.h"

/* Define --------------------------------------------------------------------*/
#define ENABLE_PUMP_FUNCTION		0

/* Local function prototypes -------------------------------------------------*/
static bool Check_Fac(void);

static void App_SetSystemReady(void *arg);
static void Task_FB_SetSystemReady(void);

static void App_WriteOverTempPROT(void *arg);
static void Task_FB_WriteOverTempPROT(void);

static void App_WriteTempTH(void *arg);
static void Task_FB_WriteTempTH(void);

static void App_SetWaterFlowPROT(void *arg);
static void Task_FB_SetWaterFlowPROT(void);

/*
static void App_SetWaterLevelProt(void *arg);
static void Task_FB_SetWaterLevelProt(void);
*/

static void App_SetHandpiecePROT(void *arg);
static void Task_FB_SetHandpiecePROT(void);

static void App_SetSafeLockEnableBit(void *arg);
static void Task_FB_SetSafeLockEnableBit(void);

static void App_SetLaserPulse(void *arg);
static void Task_FB_SetLaserPulse(void);

static void App_SetLaserPulseWidth(void *arg);
static void Task_FB_SetLaserPulseWidth(void);
	
static void App_SetLaserFrequency(void *arg);
static void Task_FB_SetLaserFrequency(void);

static void App_SetLaserPower(void *arg);
static void Task_FB_SetLaserPower(void);

static void App_SetKeyDelay(void *arg);
static void Task_FB_SetKeyDelay(void);

static void App_SetLaserModeOpt(void *arg);
static void Task_FB_SetLaserMode(void);

static void App_SetLed(void *arg);
static void Task_FB_SetLed(void);

static void App_SetLaserNum(void *arg);
static void Task_FB_SetLaserNum(void);

static void App_SetLaserIndicatorPower(void *arg);
static void Task_FB_SetLaserIndicatorPower(void);

static void App_SetWorkTime(void *arg);
static void Task_FB_SetWorkTime(void);

static void App_SetLaserCount(void *arg);
static void Task_FB_SetLaserCount(void);

static void App_GetLaserInfo(void *arg);
static void Task_FB_GetLaserInfo(void);



static void App_Updata(void *arg);
static void Task_FB_Updata(void);

static void App_ProductDate(void *arg);
static void Task_FB_ProductDate(void);

static void App_GetVersion(void *arg);
static void Task_FB_GetVersion(void);

static void App_SystemReboot(void *arg);
static void Task_FB_SystemReboot(void);

/* Variables -----------------------------------------------------------------*/
typedef struct
{
	volatile uint8_t type;
	volatile uint16_t target;
	void (*current_operation)(void *arg);
}LOCAL_APP_TABLE;

static volatile LOCAL_APP_TABLE AppTable[] = {
	{INDEX_TYPE_OPERATE,	INDEX_SYSTEM_READY,				(*App_SetSystemReady)		},
	{INDEX_TYPE_OPERATE,	INDEX_OVERTEMP_PROTECT, 	(*App_WriteOverTempPROT)},
	{INDEX_TYPE_OPERATE,	INDEX_SET_TEMP_THRESHOLD, (*App_WriteTempTH)			},
	{INDEX_TYPE_OPERATE,	INDEX_WATER_FLOW_PORTECT, (*App_SetWaterFlowPROT)	},
	{INDEX_TYPE_OPERATE,	INDEX_HANDPIECE_PROTECT, 	(*App_SetHandpiecePROT)	},
	{INDEX_TYPE_OPERATE,	SET_SAFELOCK_ENABLE, 			(*App_SetSafeLockEnableBit)},
	{INDEX_TYPE_OPERATE,	SET_LASER_PULSE_WIDTH, 		(*App_SetLaserPulseWidth)	},
	{INDEX_TYPE_OPERATE,	INDEX_LASER_PULSE, 				(*App_SetLaserPulse)	},
	{INDEX_TYPE_OPERATE,	INDEX_LASER_FREQUENCY, 		(*App_SetLaserFrequency)},
	{INDEX_TYPE_OPERATE,	INDEX_LASER_POWER, 				(*App_SetLaserPower)	},
	{INDEX_TYPE_OPERATE,	INDEX_KEY_DELAY, 					(*App_SetKeyDelay)		},
	{INDEX_TYPE_OPERATE,	INDEX_LASER_MODE, 				(*App_SetLaserModeOpt)		},
	{INDEX_TYPE_OPERATE,	INDEX_LED_CONFIG, 				(*App_SetLed)					},
	{INDEX_TYPE_OPERATE,	INDEX_LASER_NUM_CONFIG, 	(*App_SetLaserNum)		},
	{INDEX_TYPE_OPERATE,	INDEX_LASER_INDICATOR_POWER,(*App_SetLaserIndicatorPower)},
	{INDEX_TYPE_OPERATE,	INDEX_TARGET_TIME,				(*App_SetWorkTime)},	
	{INDEX_TYPE_OPERATE,	INDEX_TARGET_LASERCOUNT_MODIFY,(*App_SetLaserCount)},
	{INDEX_TYPE_OPERATE,	INFO_LASER_GET,						(*App_GetLaserInfo)},	
	
	/* Add new variables here */
	{INDEX_TYPE_OPERATE,	INDEX_TARGET_UPDATA, 			(*App_Updata)			},
	{INDEX_TYPE_OPERATE,	INDEX_TARGET_PRODUCT_DATE,(*App_ProductDate)		},
	{INDEX_TYPE_OPERATE,	INDEX_TARGET_VERSION, 		(*App_GetVersion)			},
	{INDEX_TYPE_OPERATE,	INDEX_SYSTEMRESET, 				(*App_SystemReboot)		},
};
static volatile uint8_t s_ucAppQty = sizeof(AppTable) / sizeof(AppTable[0]);

static volatile Task_Typedef TaskLocal[] = {	
/* State		RunTime		Period   current_operation */
	{ SUSPEND,	0,			1,		(*Task_FB_SetSystemReady)		},
	{ SUSPEND,	0,			1,		(*Task_FB_WriteOverTempPROT)	},
	{ SUSPEND,	0,			1,		(*Task_FB_WriteTempTH)		},
	{ SUSPEND,	0,			1,		(*Task_FB_SetWaterFlowPROT)	},
	{ SUSPEND,	0,			1,		(*Task_FB_SetHandpiecePROT)	},
	{ SUSPEND,	0,			1,		(*Task_FB_SetSafeLockEnableBit)},
	{ SUSPEND,	0,			1,		(*Task_FB_SetLaserPulse)	},
	{ SUSPEND,	0,			1,		(*Task_FB_SetLaserPulseWidth)	},
	{ SUSPEND,	0,			1,		(*Task_FB_SetLaserFrequency)},
	{ SUSPEND,	0,			1,		(*Task_FB_SetLaserPower)	},
	{ SUSPEND,	0,			1,		(*Task_FB_SetKeyDelay)		},
	{ SUSPEND,	0,			1,		(*Task_FB_SetLaserMode)		},
	{ SUSPEND,	0,			1,		(*Task_FB_SetLed)			},
	{ SUSPEND,	0,			1,		(*Task_FB_SetLaserNum)		},
	{ SUSPEND,	0,			1,		(*Task_FB_SetLaserIndicatorPower)},
	{ SUSPEND,	0,			1,		(*Task_FB_SetWorkTime)},	
	{ SUSPEND,	0,			1,		(*Task_FB_SetLaserCount)},
	{ SUSPEND,	0,			1,		(*Task_FB_GetLaserInfo)},
	
	/* Add new task here */
	{ SUSPEND,	0,			1,		(*Task_FB_Updata)			},
	{ SUSPEND,	0,			1,		(*Task_FB_ProductDate)		},
	{ SUSPEND,	0,			1,		(*Task_FB_GetVersion)			},
	{ SUSPEND,	0,			1,		(*Task_FB_SystemReboot)		},
};
static volatile uint8_t TaskLocal_Total = sizeof(TaskLocal) / sizeof(TaskLocal[0]);

/* Function prototypes -------------------------------------------------------*/
/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetSystemReady.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetSystemReady(void *arg)
{
	uint8_t *data = arg;
	bool tmp;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;
	
	tmp = (bool)data[OFFSET_DATA_CONTENT_START + 1];
	
	APP_SystemReady(tmp);
#if 1 /* Executed in function :APP_SystemReady  */
	Enable_Feedback(TASK_FB_SYSTEM_READY, 0);
#endif
}

/**
 * @brief  Task_FB_SetSystemReady.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetSystemReady(void)
{
	uint16_t state = (uint16_t)APP_IsSystemReady();
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_SYSTEM_READY, 1, &state);
	
	APP_Protect_RefreshReady();
	
	TaskLocal[TASK_FB_SYSTEM_READY].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_WriteOverTempPROT.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_WriteOverTempPROT(void *arg)
{
#if 1
	uint8_t *data = arg;
	uint8_t temp;

	temp = data[OFFSET_DATA_CONTENT_START + 1];
	APP_Mos_WriteOverTemperaturePROT((bool)temp);
	
	Enable_Feedback(TASK_FB_OVERTEMP_PROTECT, 0);
#else
	UNUSED(arg);
#endif
}

/**
 * @brief  Task_FB_WriteOverTempPROT.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_WriteOverTempPROT(void)
{
	uint16_t temp = APP_Mos_ReadOverTemperaturePROT();
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_OVERTEMP_PROTECT, 1, &temp);
	TaskLocal[TASK_FB_OVERTEMP_PROTECT].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_WriteTempTH.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_WriteTempTH(void *arg)
{
#if 1
	uint8_t *data = arg;
	uint8_t temp;

	temp = data[OFFSET_DATA_CONTENT_START + 1];
	APP_Mos_WriteTemperatrueTH(temp);
	
	Enable_Feedback(TASK_FB_SET_TEMP_TH, 0);
#else
	UNUSED(arg);
#endif
}

/**
 * @brief  Task_FB_WriteTempTH.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void Task_FB_WriteTempTH(void)
{
	uint16_t temp = APP_Water_ReadTemperatrueTH();
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_SET_TEMP_THRESHOLD, 1, &temp);
	TaskLocal[TASK_FB_SET_TEMP_TH].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetWaterFlowPROT.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetWaterFlowPROT(void *arg)
{
#if 0
	uint8_t *data = arg;
	uint8_t temp;

	temp = data[OFFSET_DATA_CONTENT_START + 1];
	APP_WriteWaterFlowPROT((bool)temp);
	
/*	Enable_Feedback(TASK_FB_SET_WATERFLOW_PROTECT, 0); */
#else
	UNUSED(arg);
#endif
}

/**
 * @brief  Task_FB_SetWaterFlowPROT.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetWaterFlowPROT(void)
{
	TaskLocal[TASK_FB_SET_WATERFLOW_PROTECT].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetWaterLevelProt.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetHandpiecePROT(void *arg)
{
	uint8_t *data = arg;
	uint8_t temp;
	uint8_t length = data[OFFSET_DATA_LENGTH];
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;
	
	for (uint8_t index = 0; index < length; index += 2)
	{
		temp = data[OFFSET_DATA_CONTENT_START + 1 + index];
		APP_WriteHandpiecePROT(index, (bool)temp);
	}

	/*	Enable_Feedback(TASK_FB_SET_HAND_PROTECT, 0); */
}

/**
 * @brief  Task_FB_SetHandpiecePROT.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetHandpiecePROT(void)
{
	TaskLocal[TASK_FB_SET_HAND_PROTECT].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetSafeLockEnableBit.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetSafeLockEnableBit(void *arg)
{
	uint8_t *data = arg;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];
	uint8_t temp;
	uint8_t length = data[OFFSET_DATA_LENGTH];
	
	if (devid != DEVICE_TYPE)
		return;
	
	for (uint8_t i = 0; i < length; i++)
	{
		temp = data[OFFSET_DATA_CONTENT_START + 1 + i * 2];
		APP_SafeLock_WritePROT(i, (bool)temp);
	}

	uint16_t respond[LOCK_ID_MAX];
	for (uint8_t i = 0; i < LOCK_ID_MAX; i++)
	{
		if (APP_SafeLock_ReadPROT(i))
			respond[i] = 0xAA;
		else
			respond[i] = 0;
	}
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, SET_SAFELOCK_ENABLE, LOCK_ID_MAX, respond);
	
	//	Enable_Feedback(TASK_FB_SET_SAFELOCK_ENABLE, 0);
}

/**
 * @brief  Task_FB_SetSafeLockEnableBit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetSafeLockEnableBit(void)
{
	TaskLocal[TASK_FB_SET_SAFELOCKER_PROTECT].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetLaserPulse.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetLaserPulse(void *arg)
{
	uint8_t *data = arg;
	uint8_t temp;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;
	
	temp = data[OFFSET_DATA_CONTENT_START + 1];
	APP_Laser_WritePulse(temp);
	
	Enable_Feedback(TASK_FB_SET_LASER_PULSE, 0);
}

/**
 * @brief  Task_FB_SetLaserPulse.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetLaserPulse(void)
{
	uint16_t state = (uint16_t)APP_LaserReadPulse();
		
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_LASER_PULSE, 1, &state);
	
	TaskLocal[TASK_FB_SET_LASER_PULSE].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetLaserPulseWidth.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetLaserPulseWidth(void *arg)
{
	uint8_t *data = arg;
	uint16_t temp;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;
	
	temp = data[OFFSET_DATA_CONTENT_START];
	temp <<= 8;
	temp += data[OFFSET_DATA_CONTENT_START + 1];
	APP_Laser_WritePulseWidth(temp);
	
	Enable_Feedback(TASK_FB_SET_LASER_PULSE_WIDTH, 0);
}

/**
 * @brief  Task_FB_SetLaserPulseWidth.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetLaserPulseWidth(void)
{
	uint16_t state = (uint16_t)APP_LaserReadPulseWidth();
		
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, SET_LASER_PULSE_WIDTH, 1, &state);
	
	TaskLocal[TASK_FB_SET_LASER_PULSE_WIDTH].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetLaserFrequency.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetLaserFrequency(void *arg)
{
	uint8_t *data = arg;
	uint8_t temp;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;
	
	temp = data[OFFSET_DATA_CONTENT_START + 1];
	APP_Laser_WriteFrequency(temp);
	
	Enable_Feedback(TASK_FB_SET_LASER_FREQUENCY, 0);
}

/**
 * @brief  Task_FB_SetLaserFrequency.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetLaserFrequency(void)
{
	uint16_t state = (uint16_t)APP_Laser_ReadFrequency();
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_LASER_FREQUENCY, 1, &state);
	
	TaskLocal[TASK_FB_SET_LASER_FREQUENCY].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetLaserPower.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetLaserPower(void *arg)
{
	uint8_t *data = arg;
	uint8_t temp;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;
	
	temp = data[OFFSET_DATA_CONTENT_START + 1];
	APP_Laser_WriteEnergy(temp);
	
	Enable_Feedback(TASK_FB_SET_LASER_POWER, 0);
}

/**
 * @brief  Task_FB_SetLaserPower.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetLaserPower(void)
{
	uint16_t state = (uint16_t)APP_Laser_ReadEnergy();
		
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_LASER_POWER, 1, &state);
		
	TaskLocal[TASK_FB_SET_LASER_POWER].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetPower.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetKeyDelay(void *arg)
{
	uint8_t *data = arg;
	uint8_t temp;
	uint8_t length = data[OFFSET_DATA_LENGTH];
	uint8_t index;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;
	
	for (index = 0; index < length; index += 2)
	{
		temp = data[OFFSET_DATA_CONTENT_START + 1 + index];
		APP_KEY_DelayConfig(index, (bool)temp);
	}
	
	Enable_Feedback(TASK_FB_SET_KEY_DELAY, 0);
}

/**
 * @brief  Task_FB_SetPower.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetKeyDelay(void)
{
	
	TaskLocal[TASK_FB_SET_KEY_DELAY].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetLaserModeOpt.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetLaserModeOpt(void *arg)
{
	uint8_t *data = arg;
	bool temp;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;
	
	temp = (bool)data[OFFSET_DATA_CONTENT_START + 1];
	APP_Laser_WriteMode(temp);
	
	Enable_Feedback(TASK_FB_SET_LASER_MODE, 0);
}

/**
 * @brief  Task_FB_SetLaserMode.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetLaserMode(void)
{
	uint16_t state = (uint16_t)(APP_Laser_ReadPulseMode());
		
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_LASER_MODE, 1, &state);
	
	TaskLocal[TASK_FB_SET_LASER_MODE].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetLed.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetLed(void *arg)
{
	uint8_t *data = arg;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];
	uint8_t state = data[OFFSET_DATA_CONTENT_START];
	uint8_t red = data[OFFSET_DATA_CONTENT_START + 1];
	uint8_t green = data[OFFSET_DATA_CONTENT_START + 2];
	uint8_t blue = data[OFFSET_DATA_CONTENT_START + 3];
	
	if (devid != DEVICE_TYPE)
		return;

	/* display color */
	APP_LED_AllConfig(state, 0xFFFF, 500, 0);
	APP_LED_ConfigColor(red, green, blue);

	/* respond */
	uint16_t respond[2];
	respond[0] = state;
	respond[0] <<= 8;
	respond[0] += red;

	respond[1] = green;
	respond[1] <<= 8;
	respond[1] += blue;

	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_LED_CONFIG, 2, respond);
	
/*	Enable_Feedback(TASK_FB_SET_LED, 0); */
}

/**
 * @brief  Task_FB_SetLed.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetLed(void)
{
	TaskLocal[TASK_FB_SET_LED].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetLaserNum.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetLaserNum(void *arg)
{
/*	
	uint8_t *data = arg;
	uint8_t temp;
	
	temp = data[OFFSET_DATA_CONTENT_START + 1];

	APP_VoltageConfig(temp);
	
	Enable_Feedback(TASK_FB_SET_LASER_NUM, 0);
*/
}

/**
 * @brief  Task_FB_SetLaserNum.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetLaserNum(void)
{
/*
	uint16_t number =  (uint16_t)APP_Voltage_OptBarNum(READ, 0);
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_LASER_NUM_CONFIG, 1, &number);
*/
	TaskLocal[TASK_FB_SET_LASER_NUM].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_FanPowerControl.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
#if 0
static void App_FanPowerControl(void *arg)
{

	uint8_t *data = arg;
	FAN_MODULE_INDEX index;
	uint8_t power;
	uint8_t length = data[OFFSET_DATA_LENGTH];
	if (length > FAN_MODULE_NUMBER) length = FAN_MODULE_NUMBER;
	for (index = FAN_MODULE_1; index < length; index++)
	{
		power = ( data[OFFSET_DATA_CONTENT_START + 1  +(index * 2)] >= 10? 10 : data[OFFSET_DATA_CONTENT_START + 1 + (index * 2)]);
		Fan_OptPowerVal(WRITE, index, power);
	}

	Enable_Feedback(TASK_FB_FAN_POWER_CONTROL, 0);
}
#endif

/**
 * @brief  Task_FB_FanPowerControl.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
#if 0
static void Task_FB_FanPowerControl(void)
{

	FAN_MODULE_INDEX index;
	uint16_t power[FAN_MODULE_NUMBER];
	for (index = FAN_MODULE_1; index < FAN_MODULE_NUMBER; index++)
	{
		power[index]= (uint16_t)Fan_OptPowerVal(READ, index, 0);
	}
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_TARGET_FAN_POWER_CONTROL, FAN_MODULE_NUMBER, power);

	TaskLocal[TASK_FB_FAN_POWER_CONTROL].State = SUSPEND;
}
#endif

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetLaserIndicatorPower.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetLaserIndicatorPower(void *arg)
{
	uint8_t *data = arg;
	uint8_t temp;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;
	
	temp = data[OFFSET_DATA_CONTENT_START + 1];
	APP_Laser_IndicatorWriteEnergy(temp);
	
	Enable_Feedback(TASK_FB_SET_LASER_INDICATOR_POWER, 0);
}

/**
 * @brief  Task_FB_SetLaserIndicatorPower.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetLaserIndicatorPower(void)
{
	uint16_t energy =  (uint16_t)APP_Laser_IndicatorReadEnergy();
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_LASER_INDICATOR_POWER, 1, &energy);
	
	TaskLocal[TASK_FB_SET_LASER_INDICATOR_POWER].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetWorkTime.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetWorkTime(void *arg)
{
	uint8_t *data = arg;
	uint8_t hour, minute, second;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;

	if (data[OFFSET_DATA_LENGTH] >= 2)
	{
		hour = data[OFFSET_DATA_CONTENT_START + 0];
		minute = data[OFFSET_DATA_CONTENT_START + 1];
		second = data[OFFSET_DATA_CONTENT_START + 2];
	
		APP_SetTime(hour, minute, second);
	}

	Enable_Feedback(TASK_FB_SET_WORK_TIME, 0);
}

/**
 * @brief  Task_FB_SetWorkTime.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetWorkTime(void)
{
//	APP_SendTime();
	TaskLocal[TASK_FB_SET_WORK_TIME].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_SetLaserCount.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SetLaserCount(void *arg)
{
	uint8_t *data = arg;
	uint32_t count;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid != DEVICE_TYPE)
		return;

	if (data[OFFSET_DATA_LENGTH] >= 2)
	{
		count = data[OFFSET_DATA_CONTENT_START + 0];
		count <<= 8;
		count += data[OFFSET_DATA_CONTENT_START + 1];
		count <<= 8;
		count += data[OFFSET_DATA_CONTENT_START + 2];
		count <<= 8;
		count += data[OFFSET_DATA_CONTENT_START + 3];
		
		APP_SetLaserCount(count);
	}

	Enable_Feedback(TASK_FB_SET_LASER_COUNT, 0);
}

/**
 * @brief  Task_FB_SetLaserCount.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SetLaserCount(void)
{
	APP_SendLaserCount();
	TaskLocal[TASK_FB_SET_LASER_COUNT].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_GetLaserInfo.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_GetLaserInfo(void *arg)
{
	uint8_t *data = arg;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];
	uint8_t state = data[OFFSET_DATA_CONTENT_START + 1];

	if (devid == DEVICE_TYPE && state == 0xAA)
		Enable_Feedback(TASK_FB_GET_LASER_INFO, 1);
}

/**
 * @brief  Task_FB_GetLaserInfo.
 * @note   Enter the shutdown.
 * @param  None.
 * @retval None.
 */
static void Task_FB_GetLaserInfo(void)
{
	uint16_t current = (uint16_t)LASER_CURRENT;
	uint16_t width = (uint16_t)LASER_WIDTH;
	uint16_t energy = (uint16_t)LASER_ENERGY;	
	uint16_t power = (uint16_t)LASER_POWER;
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INFO_LASER_CUR, 1, &current);
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INFO_LASER_WIDTH, 1, &width);	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INFO_LASER_ENERGY, 1, &energy);
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INFO_LASER_POWER, 1, &power);
	
	TaskLocal[TASK_FB_GET_LASER_INFO].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/* Enable only when debugging without IAP function */
/**
 * @brief  App_Updata.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_Updata(void *arg)
{
	uint8_t *data = arg;
	uint8_t buf;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];
	uint8_t type = data[OFFSET_DATA_CONTENT_START + 1];
	
	switch(devid)
	{
		/* Master */		
		case DEV_INDEX_MASTER:
		{
			switch(type)
			{
				case DOWN_TO_FAC:
					buf = DOWN_TO_FAC;
					break;
				case DOWN_TO_DWN:
					if (Check_Fac())
						buf = DOWN_TO_FAC;
					else
						buf = DOWN_TO_DWN;
					break;
				default:
					return;
			}
			goto __Writefalg;
		}

		/* Protect */
		case DEV_INDEX_PORTECT:
		{
			switch(type)
			{
				case DOWN_TO_DWN:
					break;
				default:
					return;
			}

			buf = DOWN_APP_0;
			goto __Writefalg;
		}

		/* Fan */
		case DEV_INDEX_FAN:
		{
			break;
		}

		/* Handpiece 0 */
		case DEV_INDEX_HANDLE_0:
		{
			break;
		}

		/* Handpiece 1 */
		case DEV_INDEX_HANDLE_1:
		{
			break;
		}
		
		default:
			break;
	}
	return;

__Writefalg:
	cf_Config_App_Flag(buf);
	
#if 0
	Enable_Feedback(TASK_FB_UPDATA, 0);
#endif
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
	uint16_t number = 0X00AA;
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_TARGET_UPDATA, 1, &number);

	HAL_Delay(1000);
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
 *		     buf.
 *		     size.
 * @retval None.
 */
#define PRODUCT_DATE_ADDR (20 * 1024 + FLASH_BASE - 4) /* Address of production date 19K + 0x08000000 */
size_t flash_read(uint32_t addr, uint8_t *buf, size_t size)
{
	uint8_t *buf_8 = (uint8_t *)buf;
	size_t index;
	for (index = 0; index < size; index++, addr++, buf_8++)
		*buf_8 = *(uint8_t *)addr;

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
	flash_read(PRODUCT_DATE_ADDR, number, 4);
	
	/* Before transferring to 16bit data transmission,
		big-endian must be adjusted, otherwise the transmission order is reversed
	*/
	for (index = 0; index < 4; index += 2)
	{
		temp = number[index];
		number[index] = number[index + 1];
		number[index + 1] = temp;
	}

	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_TARGET_PRODUCT_DATE, 2, (uint16_t *)number);
	TaskLocal[TASK_FB_PRODUCT_DATE].State = SUSPEND;
}

/* ------------------------------------------------------------------------------ */
/**
 * @brief  App_GetVersion.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_GetVersion(void *arg)
{
	uint8_t *data = arg;
	uint8_t devid = data[OFFSET_DATA_TARGET_H];

	if (devid == DEVICE_TYPE)
		Enable_Feedback(TASK_FB_GET_VERSION, 0);
	else if (devid == DEV_INDEX_PORTECT)
		Task_FB_Protect_Enable(TASK_FB_PROTECT_VERSION, 0);
}

/**
 * @brief  Task_FB_GetVersion.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_GetVersion(void)
{
	uint16_t temp[2];
	temp[0] = (uint16_t)(BSP_SOFTWARE_VERSION >> 16);
	temp[1] = (uint16_t)(BSP_SOFTWARE_VERSION);
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_TARGET_VERSION, 2, temp);
	
	TaskLocal[TASK_FB_GET_VERSION].State = SUSPEND;	
}

/* --------------------------------------------------------------------------- */
#if ENABLE_PUMP_FUNCTION
/**
 * @brief  App_PumpControl.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_PumpControl(void *arg)
{
	uint8_t *data = arg;
	if (data[OFFSET_DATA_CONTENT_START + 1])
	{
		Water_PumpControl(1);
	}
	else
	{
		Water_PumpControl(0);
	}

	Enable_Feedback(TASK_FB_PUMP_CONTROL, 0);
}

/**
 * @brief  Task_FB_PumpControl.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_PumpControl(void)
{
	uint16_t state;

	state = (DEV_PUMP_STATE == DEV_PUMP_ON ? 0X0001 : 0X0000);
	/* Feedback data */
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_TARGET_PUMP_CONTROL, 1, &state);
	TaskLocal[TASK_FB_PUMP_CONTROL].State = SUSPEND;
}
#endif /* ENABLE_PUMP_FUNCTION */

/* --------------------------------------------------------------------------- */
/**
 * @brief  App_SystemReboot.
 * @note   None.
 * @param  arg.
 * @retval None.
 */
static void App_SystemReboot(void *arg)
{
	Enable_Feedback(TASK_FB_SYSTEM_REBOOT, 0);
}

/**
 * @brief  Task_FB_SystemReboot.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void Task_FB_SystemReboot(void)
{
	HAL_Delay(1000);
	HAL_FLASH_OB_Launch();
#if 0
	TaskLocal[TASK_FB_SYSTEM_REBOOT].State = SUSPEND;
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
		if (TaskLocal[index].RunTime == 0 && (TaskLocal[index].State == READY))
		{
			TaskLocal[index].TaskHook();
			TaskLocal[index].RunTime = TaskLocal[index].Period;
		}
	}
}

/* --------------------------------------------------------------------------- */
/**
 * @brief  Enable_Feedback.
 * @note   None.
 * @param  index.
 *			DelayState.
 * @retval None.
 */
void Enable_Feedback(uint8_t id, uint8_t delaystate)
{
	if (delaystate)
		delaystate = TaskLocal[id].Period;

	TaskLocal[id].RunTime = delaystate;
	TaskLocal[id].State = READY;
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
		
	if (dev == DEVICE_TYPE || dev == DEV_INDEX_PORTECT)
		;
	else
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

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
static bool Check_Fac(void)
{
#if defined(ENABLE_FAL_SUPPORT)
	#define FILE_LENGTH 4
	
	/* Read Size */
	uint32_t filesize = 0;
	uint8_t buff[FILE_LENGTH];

	const struct fal_partition *part = fal_partition_find("fac");
	if (part == NULL)
		return false;

	if (fal_partition_read(part, 0, buff, FILE_LENGTH) < FILE_LENGTH)
		return false;

	/* Calculate size */
	for (uint8_t i = 0; i < FILE_LENGTH; i++)
	{
		filesize <<= 8;
		filesize += buff[i];
	}

	/*  */
	if (filesize == 0 || filesize == 0xFFFFFFFF)
		return true;
	else
		return false;
#else
		return false;
#endif /* ENABLE_FAL_SUPPORT */
}
