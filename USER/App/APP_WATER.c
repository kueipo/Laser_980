
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define WATER_SPEED_TH	20

__IOM WaterModel_Struct s_stWaterTcb;

static uint8_t WaterTemperature_Detection(void);

void APP_Water_Init(void)
{
	memset((uint8_t *)&s_stWaterTcb, 0, sizeof(s_stWaterTcb));

	s_stWaterTcb.ucLevel = WATER_LOW;
	s_stWaterTcb.ucTemperature = 0;
	s_stWaterTcb.uiSpeed = 0;
	s_stWaterTcb.ucTemperatureTH = 36;
	s_stWaterTcb.ucSpeedDelay = 1;
	s_stWaterTcb.bOverTempProtect = true;
	s_stWaterTcb.bFlowProtect = true;
	s_stWaterTcb.bLevelProtect = true;
}

void APP_Water_Task(void)
{
	static uint8_t index = 0;
	switch (index)
	{
	case WATER_LEVEL:
	{
		s_stWaterTcb.ucLevel = BSP_ReadWaterLevel();
	}
	break;

	case WATER_TEMPERATURE:
	{
		s_stWaterTcb.ucTemperature = WaterTemperature_Detection();
	}
	break;

	case WATER_SPEED:
	{
		if (s_stWaterTcb.ucSpeedDelay)
		{
			s_stWaterTcb.ucSpeedDelay--;
			s_stWaterTcb.uiSpeed = WATER_SPEED_TH;
		}
		else
		{
			s_stWaterTcb.uiSpeed = BSP_ReadWaterSpeed();
		}
	}
	break;

	default:
		break;
	}
	if (++index >= WATER_MAX)
		index = 0;
}

/**
 * @brief  WaterTemperature_Detection.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static uint8_t WaterTemperature_Detection(void)
{
#if 0
	Vref = AdcValue[ADC_VREF_INDEX];
	Vref = 1.2 / Vref;
	temperature = AdcValue[ADC_MCU_TEMP_INDEX];
	temperature = Vref*temperature;
#endif

	uint8_t index = 0xff;
	uint16_t temp = BSP_ReadADCVal(WATER_TEMP_CHNL);

	for (index = 0; index < TEMP_TABLES_LENGTH; index++)
	{
		if (temp <= NTC50K3950[index])
			break;
	}
	return index;
}

/**
 * @brief  APP_ReadWaterLevel.
 * @note   None.
 * @param  None.
 * @retval Level.
 */
uint8_t APP_ReadWaterLevel(void)
{
	return s_stWaterTcb.ucLevel;
}

/**
 * @brief  APP_ReadWaterTemperature.
 * @note   None.
 * @param  None.
 * @retval Temperature.
 */
uint8_t APP_ReadWaterTemperature(void)
{
	return s_stWaterTcb.ucTemperature;
}

/**
 * @brief  APP_ReadWaterFlow.
 * @note   None.
 * @param  None.
 * @retval Speed.
 */
uint8_t APP_ReadWaterFlow(void)
{
	return (uint8_t)s_stWaterTcb.uiSpeed;
}

/**
 * @brief  APP_WriteWaterTemperatrueTH.
 * @note   None.
 * @param  val.
 * @retval None.
 */
void APP_WriteWaterTemperatrueTH(uint8_t val)
{
	s_stWaterTcb.ucTemperatureTH = val;
}

/**
 * @brief  APP_WriteWaterOverTemperaturePROT.
 * @note   Noneֵ
 * @param  bState.
 * @retval None.
 */
void APP_WriteWaterOverTemperaturePROT(bool bState)
{
	s_stWaterTcb.bOverTempProtect = bState;
}

/**
 * @brief  APP_WriteWaterFlowPROT.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_WriteWaterFlowPROT(bool bState)
{
	s_stWaterTcb.bFlowProtect = bState;
}

/**
 * @brief  APP_WriteWaterLevelPROT.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_WriteWaterLevelPROT(bool bState)
{
	s_stWaterTcb.bLevelProtect = bState;
}

/**
 * @brief  WaterTemperatureOver.
 * @note   None.
 * @param  None.
 * @retval bool.
 */
bool APP_IsWaterTemperatureOver(void)
{
	if (s_stWaterTcb.ucTemperature > s_stWaterTcb.ucTemperatureTH)
		return true;
	else
		return false;
}

/**
 * @brief  APP_IsWaterFlowErr.
 * @note   None.
 * @param  None.
 * @retval bool.
 */
bool APP_IsWaterFlowErr(void)
{
	if (s_stWaterTcb.bFlowProtect)
	{
		if (s_stWaterTcb.uiSpeed < WATER_SPEED_TH)
		{
			return true;
		}
	}
	return false;
}

/**
 * @brief  APP_IsWaterLevelErr.
 * @note   None.
 * @param  None.
 * @retval Results.
 */
bool APP_IsWaterLevelErr(void)
{
	if (s_stWaterTcb.bLevelProtect)
	{
		if (s_stWaterTcb.ucLevel > WATER_LOW)
			return true;
	}
	return false;
}

/**
 * @brief  APP_WaterSpeedInit.
 * @note   None.
 * @param  ucDelay.
 * @retval None.
 */
void APP_WaterSpeedInit(uint8_t ucDelay)
{
	s_stWaterTcb.ucSpeedDelay = ucDelay;
	s_stWaterTcb.uiSpeed = WATER_SPEED_TH;
}
