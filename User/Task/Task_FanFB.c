
/* Includes ------------------------------------------------------------------*/
#include "Task/Task_Common.h"
#include "DEV_Config.h"

/* Define --------------------------------------------------------------------*/
#if EX_FAN_MAX_MUNBER

#define	FAN_OFFSET_STEP						(uint8_t)0X01
#define	FAN_OFFSET_FRAME_LENGTH 	(uint8_t)0X00																					/* 00 */
#define	FAN_OFFSET_DATA_TYPE			(uint8_t)(FAN_OFFSET_STEP + FAN_OFFSET_FRAME_LENGTH)	/* 01 */
#define FAN_OFFSET_DATA_TARGET_H	(uint8_t)(FAN_OFFSET_STEP + FAN_OFFSET_DATA_TYPE)			/* 02 */
#define FAN_OFFSET_DATA_TARGET_L	(uint8_t)(FAN_OFFSET_STEP + FAN_OFFSET_DATA_TARGET_H)	/* 03 */
#define	FAN_OFFSET_DATA_LENGTH		(uint8_t)(FAN_OFFSET_STEP + FAN_OFFSET_DATA_TARGET_L)	/* 04 */
#define FAN_OFFSET_DATA_CONTENT_START	\
																	(uint8_t)(FAN_OFFSET_STEP + FAN_OFFSET_DATA_LENGTH)		/* 05 */

#ifndef INDEX_TYPE_OPERATE
#define INDEX_TYPE_OPERATE				(uint8_t)0X83
#endif

#ifndef INDEX_TYPE_READ
#define INDEX_TYPE_READ						(uint8_t)0X82
#endif

#ifndef INDEX_TYPE_FEEDBACK
#define INDEX_TYPE_FEEDBACK				INDEX_TYPE_OPERATE - 1
#endif

#ifndef INDEX_TYPE_HEARTBEAT
#define INDEX_TYPE_HEARTBEAT			(uint8_t)0X82
#endif

#ifndef TARGET_LENGTH
#define TARGET_LENGTH							(uint16_t)0x0001
#endif

/* Function prototypes -------------------------------------------------------*/
static void Fan_PowerVal(void *arg);
static void Fan_TemperatureVal(void *arg);
static void Fan_PowerAuto(void *arg);
static void Fan_SpeedVal(void *arg);
static void Fan_Number(void *arg);
//static Execute_StatusTypeDef ViceSend_Data(uint8_t Type, uint16_t Targe, uint8_t Length, uint16_t *pData);

/* Variables -----------------------------------------------------------------*/
typedef struct
{
	volatile uint8_t	type;
	volatile uint16_t	target;
	void (*current_operation)(void *arg);
}Local_APP_Table;

static Local_APP_Table AppTable[] = {
	{INDEX_TYPE_FEEDBACK,	INDEX_TARGET_FAN_POWER_CONTROL,	(*Fan_PowerVal )		},
	{INDEX_TYPE_FEEDBACK,	INDEX_TARGET_FAN_TEMPERATURE, 	(*Fan_TemperatureVal )	},
	{INDEX_TYPE_FEEDBACK,	INDEX_TARGET_FAN_POWER_AUTO, 		(*Fan_PowerAuto )		},
	{INDEX_TYPE_FEEDBACK,	INDEX_TARGET_FAN_SPEED, 				(*Fan_SpeedVal )		},
	{INDEX_TYPE_FEEDBACK,	INDEX_TARGET_FAN_NUMBER, 				(*Fan_Number )			},
};
static volatile uint8_t AppQty = sizeof(AppTable)/sizeof(AppTable[0]);

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  FanPowerVal.
 * @note   None.
 * @param  *arg.
 * @retval None.
 */
static void Fan_PowerVal(void *arg)
{
#if 0
	uint8_t *data = arg;	
	uint8_t index;
	uint8_t speed;
	uint8_t length = data[OFFSET_DATA_LENGTH];
	for (index = 0; index < length; index++)
	{
		speed =  data[OFFSET_DATA_CONTENT_START +1 +(index *2)];
		OPT_FanPowerVal(WRITE, index, speed);
	}
#else
	UNUSED(arg);
#endif
}

/**
 * @brief  FanTemperatureVal.
 * @note   None.
 * @param  *arg.
 * @retval None.
 */
static void Fan_TemperatureVal(void *arg)
{
#if 0
	uint8_t *data = arg;
	uint8_t index;
	uint8_t val;
	uint8_t length = data[OFFSET_DATA_LENGTH];
	for (index = 0; index < length; index++)
	{
		val = data[OFFSET_DATA_CONTENT_START + 1 + (index * 2)];
		OPT_FanTemperatureVal(WRITE, index, val);
	}
#else
	UNUSED(arg);
#endif
}

/**
 * @brief  FanPowerAuto.
 * @note   None.
 * @param  *arg.
 * @retval None.
 */
static void Fan_PowerAuto(void *arg)
{
#if 0
	uint8_t *data = arg;
	uint8_t index;
	uint8_t val;
	uint8_t length = data[OFFSET_DATA_LENGTH];
	for (index = 0; index < length; index++)
	{
		val = data[OFFSET_DATA_CONTENT_START + 1 + (index * 2)];
		OPT_AutoFanPower(WRITE, index, val);
	}
#else
	UNUSED(arg);
#endif
}

/**
 * @brief  FanSpeedVal.
 * @note   None.
 * @param  *arg.
 * @retval None.
 */
static void Fan_SpeedVal(void *arg)
{
	// external fan
#if EX_FAN_MAX_MUNBER
	uint8_t *data = arg;
	uint8_t index;
	uint16_t val;
	uint8_t length = data[OFFSET_DATA_LENGTH];
	for (index = 0; index < length; index++)
	{
		val = data[OFFSET_DATA_CONTENT_START + (index * 2)];
		val <<= 8;
		val += data[OFFSET_DATA_CONTENT_START + (index * 2) + 1];

		APP_Fan_OptSpeedVal(WRITE, EX_FAN_MODULE, index, val);
	}
#else
	UNUSED(arg);
#endif
}

/**
 * @brief  FanNumber.
 * @note   None.
 * @param  *arg.
 * @retval None.
 */
static void Fan_Number(void *arg)
{
#if 0
	uint8_t *data = arg;
	uint8_t val;

	val = data[OFFSET_DATA_CONTENT_START+1] ;	
	OPT_FanNumber(WRITE, val);
#else
	UNUSED(arg);
#endif
}

/**
 * @brief  ViceSend_Data.
 * @note   None.
 * @param  Type.
 * @param  Targe.
 * @param  Length.
 * @param  pData.
 * @retval result.
 */
#if 0
static Execute_StatusTypeDef ViceSend_Data(uint8_t Type, uint16_t Targe, uint8_t Length, uint16_t *pData)
{
	uint8_t offset;
	uint8_t index = 0;
	uint8_t databuf[32] = {0};
#if USING_CRC16
	uint16_t crc;
#endif

	uint16_t targe = Targe - FEEDBACK_DIFFERENCE;

	databuf[index++] = 0XA5;
	databuf[index++] = 0X5A;
	/* OFFSET_FRAME_LENGTH				8bit */
	databuf[index++] = 1 + 2 + (Length * 2) + 1;
	/* OFFSET_DATA_TYPE					8bit */
	databuf[index++] = Type;
	/* OFFSET_DATA_TARGET				16bit */
	databuf[index++] = (uint8_t)((targe & 0xff00) >> 8);
	databuf[index++] = (uint8_t)(targe & 0x00ff);
	/* OFFSET_DATA_LENGTH				8bit */
	databuf[index++] = Length;
	/* OFFSET_DATA_CONTENT_START 		16bit */
	for (offset = 0; offset < Length; offset++)
	{
		databuf[index++] = (uint8_t)((pData[offset] & 0xff00) >> 8);
		databuf[index++] = (uint8_t)(pData[offset] & 0x00ff);
	}

#if USING_CRC16
	crc = IOT_CRC16_XMODEM(databuf + 3, index - 3);
	databuf[2] += 2;
	databuf[index++] = crc >> 8;
	databuf[index++] = crc & 0xff;
#endif

	if (HAL_UART_Transmit(DEV_SLAVEUART_PORT, (uint8_t *)databuf, index, 0xff) != HAL_OK)
	{
		/* Reset Tx transfer counter */
		DEV_SLAVEUART_PORT->TxXferCount = 0x00U;
		/* Restore huart->gState to Ready */
		DEV_SLAVEUART_PORT->gState = HAL_UART_STATE_READY;
		return EXE_TIMEOUT;
	}
	return EXE_OK;
}
#endif
/* -------------------------------------------------------------------------------- */
/**
 * @brief  Task_Fan_AppMatching.
 * @note   None.
 * @param  *buf.
 * @retval None.
 */
void Task_Fan_AppMatching(void *arg)
{
	uint8_t *data = arg;
	uint8_t type = data[OFFSET_DATA_TYPE];
	uint8_t dev = data[OFFSET_DATA_TARGET_H];
	uint8_t target = data[OFFSET_DATA_TARGET_L];
	
	if (dev != DEV_INDEX_FAN)
		return;
	
	for (uint8_t index = 0; index < AppQty; index++)
	{
		if ((AppTable[index].type == type) && (AppTable[index].target == target))
		{
			AppTable[index].current_operation(data);
			break;
		}
	}
}

#else
void Task_Fan_AppMatching(void *arg)
{}
#endif
