
/* Includes ------------------------------------------------------------------*/
#include "Task/Task_Common.h"

/* Define --------------------------------------------------------------------*/
#define ENABLE_SEND_VERSION 1
#define ENABLE_SEND_FAN_SPEED 0
#define ENABLE_SEND_FAN_TEMPERATURE 0
#define ENABLE_SEND_FAN_POWER 0
#define ENABLE_SEND_ACVOLTAGE 1
#define ENABLE_SEND_WATER_TEMPERATURE 0
#define ENABLE_SEND_WATER_FLOW 0
#define ENABLE_SEND_WATER_LEVEL 0
#define ENABLE_SEND_COOLER_INFO	0
#define ENABLE_SEND_PUMP_INFO 0
#define ENABLE_SEND_MOS_TEMPERATURE 1

/* Function prototypes -------------------------------------------------------*/
static void SendErrorInfo(void);

#if ENABLE_SEND_WATER_TEMPERATURE
static void SendWaterTemperature(void);
#endif /* ENABLE_SEND_WATER_TEMPERATURE */

#if ENABLE_SEND_WATER_FLOW
static void SendWaterFlowSpeed(void);
#endif /* ENABLE_SEND_WATER_FLOW */

#if ENABLE_SEND_WATER_LEVEL
static void SendWaterLevel(void);
#endif /* ENABLE_SEND_WATER_LEVEL */

static void SendHandPieceConn(void);

#if ENABLE_SEND_VERSION
static void SendVersion(void);
#endif /* ENABLE_SEND_VERSION */

#if ENABLE_SEND_COOLER_INFO
static void SendCoolerElInfor(void);
#endif /* ENABLE_SEND_COOLER_INFO */

#if ENABLE_SEND_PUMP_INFO
static void SendPumpElInfor(void);
#endif /* ENABLE_SEND_PUMP_INFO */

static void SendSafeLockerInfor(void);

#if ENABLE_SEND_FAN_SPEED
void SendFanCurrentSpeedInfo(void);
#endif /* ENABLE_SEND_FAN_SPEED */

#if ENABLE_SEND_FAN_TEMPERATURE
void SendFanCurrentTemperature(void);
#endif /* ENABLE_SEND_FAN_TEMPERATURE */

#if ENABLE_SEND_ACVOLTAGE
void SendACVoltage(void);
#endif /* ENABLE_SEND_ACVOLTAGE */

#if ENABLE_SEND_FAN_POWER
void SendFanPower(void);
#endif /* ENABLE_SEND_FAN_POWER */

void SendDC05Info(void);
void SendDC12Info(void);
void SendDCLdInfo(void);

#if ENABLE_SEND_MOS_TEMPERATURE
static void SendMosTemperature(void);
#endif /* ENABLE_SEND_MOS_TEMPERATURE */

/* Variables -----------------------------------------------------------------*/
uint8_t heattest = 0;
uint8_t Hz = 1;
uint16_t J = 10;
uint8_t power = 1;

typedef struct
{
	void (*TaskHook)(void);
} TaskLocal_TypeDef;

static TaskLocal_TypeDef TaskLocal[] = {
	{*SendErrorInfo},
#if ENABLE_SEND_WATER_TEMPERATURE
	{*SendWaterTemperature},
#endif /* ENABLE_SEND_WATER_TEMPERATURE */
#if ENABLE_SEND_WATER_FLOW
	{*SendWaterFlowSpeed},
#endif /* ENABLE_SEND_WATER_FLOW */
	
#if ENABLE_SEND_WATER_LEVEL
	{*SendWaterLevel},
#endif /* ENABLE_SEND_WATER_LEVEL */
	{*SendHandPieceConn},
#if ENABLE_SEND_VERSION
	{*SendVersion},
#endif /* ENABLE_SEND_VERSION */
#if ENABLE_SEND_COOLER_INFO
	{*SendCoolerElInfor},
#endif /* ENABLE_SEND_COOLER_INFO */
#if ENABLE_SEND_PUMP_INFO
	{*SendPumpElInfor},
#endif /* ENABLE_SEND_PUMP_INFO */
	
	{*SendSafeLockerInfor},

#if ENABLE_SEND_FAN_SPEED
	{*SendFanCurrentSpeedInfo},
#endif /* ENABLE_SEND_FAN_SPEED */
#if ENABLE_SEND_FAN_TEMPERATURE
	{*SendFanCurrentTemperature},
#endif /* ENABLE_SEND_FAN_TEMPERATURE */
	{*SendACVoltage},
#if ENABLE_SEND_FAN_POWER
	{*SendFanPower},
#endif /* ENABLE_SEND_FAN_POWER */
	
	{*SendDC05Info},
	{*SendDC12Info},
	{*SendDCLdInfo},
#if ENABLE_SEND_MOS_TEMPERATURE
	{*SendMosTemperature},
#endif /* ENABLE_SEND_MOS_TEMPERATURE */
	
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

#if 0 /* Indicator */
	DEV_LED_G_TOGGLE;
#endif
	APP_LED_TimeProc(100);

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
static void SendErrorInfo(void)
{
#if 0
	uint32_t state = Read_DeviceState();
	uint16_t buff[2] = {0};
	
	buff[0] = state >> 16;
	buff[1] = state;

	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_TARGET_HB_ERROR, 2, buff);
#endif
}

/**
 * @brief  SendWaterTemperature.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_WATER_TEMPERATURE
static void SendWaterTemperature(void)
{
	uint16_t tmp = (uint16_t)APP_ReadWaterTemperature();
//	uint16_t tmp = (uint16_t)APP_ReadMosTemperature();
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_TARGET_WATER_TEMPERATURE, 1, &tmp);
}
#endif /* ENABLE_SEND_WATER_TEMPERATURE */

/**
 * @brief  Send water flow speed.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_WATER_FLOW
static void SendWaterFlowSpeed(void)
{
	uint16_t tmp = (uint16_t)APP_ReadWaterFlow();
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_TARGET_WATER_SPEED, 1, &tmp);
}
#endif /* ENABLE_SEND_WATER_FLOW */

/**
 * @brief  Send water level.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_WATER_LEVEL
static void SendWaterLevel(void)
{
	uint16_t tmp = (uint16_t)APP_ReadWaterLevel();
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_TARGET_WATER_LEVEL, 1, &tmp);
}
#endif /* ENABLE_SEND_WATER_LEVEL */

/**
 * @brief  Send Handpiece connect state.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void SendHandPieceConn(void)
{
	uint16_t tmp[HANDPIECE_ID_MAX];
	uint8_t index;
	
	for (index = 0; index < HANDPIECE_ID_MAX; index++)
		tmp[index] = (uint16_t)APP_ReadHandpieceCONN(index);
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_HANDPIECE_CONN, HANDPIECE_ID_MAX, tmp);
}

/**
 * @brief  SendVersion.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_VERSION
static void SendVersion(void)
{
	Enable_Feedback(TASK_FB_GET_VERSION, 0);
}
#endif /* ENABLE_SEND_VERSION */

/**
 * @brief  SendCoolerElInfor.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_COOLER_INFO
static void SendCoolerElInfor(void)
{

	uint16_t tmp;

	tmp = APP_ReadCoolerVoltage(COOLER_0);
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_COOLER_VOLTAGE, 1, &tmp);

	tmp = (uint16_t)APP_ReadCoolerCurrent(COOLER_0);
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_COOLER_CURRENT, 1, &tmp);
}
#endif /* ENABLE_SEND_COOLER_INFO */

/**
 * @brief  SendPumpElInfor.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_PUMP_INFO
static void SendPumpElInfor(void)
{

	uint16_t tmp;

	tmp = APP_ReadPumpVoltage();
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_PUMP_VOLTAGE, 1, &tmp);

	tmp = (uint16_t)APP_ReadPumpCurrent();
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_PUMP_CURRENT, 1, &tmp);
}
#endif /* ENABLE_SEND_PUMP_INFO */

/**
 * @brief  SendSafeLockerInfor.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void SendSafeLockerInfor(void)
{
	uint16_t tmp[LOCKER_ID_MAX];

	for (uint8_t index = 0; index < LOCKER_ID_MAX; index++)
	{
		tmp[index] = (uint16_t)APP_ReadSafeLockerConn(index);
	}
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_SAFELOCKER_STATE, LOCKER_ID_MAX, tmp);
}

#if ENABLE_SEND_FAN_SPEED
/**
 * @brief  Send fan speed value.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void SendFanCurrentSpeedInfo(void)
{
	uint16_t speed[IN_FAN_MAX_MUNBER + EX_FAN_MAX_MUNBER] = {0};
	uint8_t index;

	for (index = 0; index < IN_FAN_MAX_MUNBER + EX_FAN_MAX_MUNBER; index++)
	{	
		if (index < IN_FAN_MAX_MUNBER)
	#if IN_FAN_MAX_MUNBER
			speed[index] = APP_Fan_OptSpeedVal(READ, IN_FAN_MODULE, index, 0);
	#else
			;
	#endif			
		else
	#if EX_FAN_MAX_MUNBER
			speed[index] = APP_Fan_OptSpeedVal(READ, EX_FAN_MODULE, index - IN_FAN_MAX_MUNBER, 0);
	#else
			;
	#endif
	}
#if IN_FAN_MAX_MUNBER || EX_FAN_MAX_MUNBER
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_FAN_SPEED, index, speed);
#endif
}
#endif /* ENABLE_SEND_FAN_SPEED */

/**
 * @brief  Send the temperature of the fan module.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_FAN_TEMPERATURE
void SendFanCurrentTemperature(void)
{
	FAN_MODULE_ENUM id;
	uint16_t temperature[FAN_MODULE_ENUM];
	for (id = 0; id < FAN_MODULE_ENUM; id++)
	{
		temperature[id] = (uint16_t)Fan_OptTemperatureVal(READ, id, 0);
	}
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_TARGET_TEMPERATURE, FAN_MODULE_ENUM, temperature);
}
#endif /* ENABLE_SEND_FAN_TEMPERATURE */

/**
 * @brief  Send AC Voltage.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_ACVOLTAGE
void SendACVoltage(void)
{
	uint16_t AcVoltage = Voltage_Read();
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_AC_VOLTAGE, 1, &AcVoltage);
}
#endif /* ENABLE_SEND_ACVOLTAGE */

/**
 * @brief  Send the power of fan.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_SEND_FAN_POWER
void SendFanPower(void)
{
	FAN_MODULE_ENUM id;
	uint16_t power[FAN_MODULE_MAX_NUMBER];
	for (id = 0; id < FAN_MODULE_MAX_NUMBER; id++)
	{
		power[id] = (uint16_t)Fan_OptPowerVal(READ, id, 0);
	}
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_TARGET_FAN_POWER_CONTROL, FAN_MODULE_MAX_NUMBER, power);
}
#endif /* ENABLE_SEND_FAN_POWER */

/**
 * @brief  SendDC05Info.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void SendDC05Info(void)
{
	uint16_t val = (uint16_t)APP_VoltageDetectionRead(INDEX_DC5V);

	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_DC05_INFO, 1, &val);
}

/**
 * @brief  SendDC12Info.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void SendDC12Info(void)
{
	uint16_t val = (uint16_t)APP_VoltageDetectionRead(INDEX_DC12V);

	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_DC12_INFO, 1, &val);
}

/**
 * @brief  SendDCLdInfo.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void SendDCLdInfo(void)
{
	uint16_t val = (uint16_t)APP_VoltageDetectionRead(INDEX_DCLD);

	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_DCLD_INFO, 1, &val);
}

#if ENABLE_SEND_MOS_TEMPERATURE
/**
 * @brief  SendWaterTemperature.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void SendMosTemperature(void)
{
	uint16_t tmp = (uint16_t)APP_ReadMosTemperature();
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_MOS_TEMPERATURE, 1, &tmp);
}
#endif /* ENABLE_SEND_FAN_POWER */
