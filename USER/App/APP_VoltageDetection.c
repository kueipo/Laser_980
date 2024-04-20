
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

__IOM VoltegeDetection_Struct s_stVoltageDeteTcb[VOLTAGEDETECTION_MAX] = {
	/* DC12V */
	{
		.ucThreshold_H = 125,
		.ucThreshold_L = 115,
		.ucActual = 0,
		.ucRatio = 150, /* 25 * ((100 + 20) / 20) */
		.channel = V12_VOL_CHNL,
		.bProtect = true,
	},
	/* DC5V */
	{
		.ucThreshold_H = 45,
		.ucThreshold_L = 55,
		.ucActual = 0,
		.ucRatio = 75, /* 25 * ((20 + 10) / 10) */
		.channel = V05_VOL_CHNL,
		.bProtect = true,
	},
	/* DCLD */
	{
		.ucThreshold_H = 100,
		.ucThreshold_L = 10,
		.ucActual = 0,
		.ucRatio = 74, /* 25 * ((100 + 51) / 51) */
		.channel = VLD_VOL_CHNL,
		.bProtect = true,
	},	
};

 uint8_t Voltage_Detection(uint8_t unIndex);

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
 * @brief  APP_Water_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_VoltageDetection_Task(void)
{
	static uint8_t index = 0;
	
	s_stVoltageDeteTcb[index].ucActual = Voltage_Detection(index);
	
	if (++index >= VOLTAGEDETECTION_MAX)
		index = 0;
}

/**
  * @brief  PumpVoltage_Detection.
  * @note   None.
  * @param  None.
  * @retval PumpVolADC.
  */
 uint8_t Voltage_Detection(uint8_t unIndex)
{
	uint8_t channel = s_stVoltageDeteTcb[unIndex].channel;
	uint32_t VolADC = (uint32_t)BSP_ReadADCVal(channel);
	uint16_t Ratio = s_stVoltageDeteTcb[unIndex].ucRatio;
#if 0	/* Use internal reference voltage */
	VolADC *= 1320;
	VolADC /=  BSP_ReadADCVal(channel);
#else	/* Use external reference voltage */
	VolADC *= Ratio;
	VolADC >>= 12;

#endif
	return (uint8_t)VolADC;
}

/**
  * @brief  APP_VoltageDetectionRead.
  * @note   None.
  * @param  unIndex.
  * @retval Actual.
  */
uint8_t APP_VoltageDetectionRead(uint8_t unIndex)
{
	if (unIndex >= VOLTAGEDETECTION_MAX)
		return 0xFF;
	
	return s_stVoltageDeteTcb[unIndex].ucActual;
}
