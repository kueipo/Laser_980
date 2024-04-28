
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* variables -----------------------------------------------------------------*/
VoltegeDetection_Struct s_stVoltageDeteTcb[VOLTAGEDETECTION_MAX] = {
	/* DC12V */
	{
		.ucThreshold_H = 125,
		.ucThreshold_L = 115,
		.usVoltage = 0,
		.ucRatio = 150, /* 25 * ((100 + 20) / 20) */
		.channel = V12_VOL_CHNL,
		.bProtect = true,
	},
	/* DC5V */
	{
		.ucThreshold_H = 55,
		.ucThreshold_L = 45,
		.usVoltage = 0,
		.ucRatio = 75, /* 25 * ((20 + 10) / 10) */
		.channel = V05_VOL_CHNL,
		.bProtect = true,
	},
	/* DCLD */
	{
		.ucThreshold_H = 60,
		.ucThreshold_L = 40,
		.usVoltage = 0,
		.ucRatio = 150, /* 25 * ((100 + 20) / 20) */
		.channel = VLD_VOL_CHNL,
		.bProtect = true,
	},	
};

/* function prototypes -------------------------------------------------------*/
static uint16_t Voltage_Detection(uint8_t id);

/* Exported functions --------------------------------------------------------*/
/**
 * @brief  APP_VoltageDetection_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_VoltageDetection_Init(void)
{
}

/**
 * @brief  APP_VoltageDetection_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_VoltageDetection_Task(void)
{
	static uint8_t id = 0;
	
	s_stVoltageDeteTcb[id].usVoltage = Voltage_Detection(id);
	
	if (++id >= VOLTAGEDETECTION_MAX)
		id = 0;
}

/**
  * @brief  APP_VoltageDetection_Read.
  * @note   None.
  * @param  id.
  * @retval Voltage.
  */
uint16_t APP_VoltageDetection_Read(uint8_t id)
{
	if (id >= VOLTAGEDETECTION_MAX)
		return 0xFF;

	return s_stVoltageDeteTcb[id].usVoltage;
}

/**
  * @brief  APP_VoltageDetection_IsError.
  * @note   None.
  * @param  None.
  * @retval Result.
  */
bool APP_VoltageDetection_IsError(void)
{
	for (uint8_t i = 0; i < VOLTAGEDETECTION_MAX; i++)
	{
		if (s_stVoltageDeteTcb[i].usVoltage > s_stVoltageDeteTcb[i].ucThreshold_H ||
			  s_stVoltageDeteTcb[i].usVoltage < s_stVoltageDeteTcb[i].ucThreshold_L)
			return true;
	}
	return false;
}

/**
  * @brief  Voltage_Detection.
  * @note   None.
  * @param  id.
  * @retval volAdc.
  */
static uint16_t Voltage_Detection(uint8_t id)
{
	uint8_t channel = s_stVoltageDeteTcb[id].channel;
	uint32_t volAdc = (uint32_t)BSP_ReadADCVal(channel);
	uint16_t ratio = s_stVoltageDeteTcb[id].ucRatio;
	
#if 0	/* Use internal reference voltage */
	volAdc *= 1320;
	volAdc /=  BSP_ReadADCVal(channel);
#else	/* Use external reference voltage */
	volAdc *= ratio;
	volAdc >>= 12;
#endif
	
	return (uint16_t)volAdc;
}
