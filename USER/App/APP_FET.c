
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

__IOM Fet_Struct s_stFetTcb;

static uint8_t FetTemperature_Detection(void);

/**
 * @brief  APP_Fet_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Fet_Init(void)
{
    memset((uint8_t*)&s_stFetTcb, 0, sizeof(s_stFetTcb));
	
	s_stFetTcb.ucTemperature = 0;
	s_stFetTcb.ucTemperatureTH = 40;
	s_stFetTcb.bOverTempProtect = true;
}

/**
 * @brief  APP_Fet_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Fet_Task(void)
{
	s_stFetTcb.ucTemperature = FetTemperature_Detection();
}

/**
 * @brief  FetTemperature_Detection.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static uint8_t FetTemperature_Detection(void)
{
#if 0
	Vref = AdcValue[ADC_VREF_INDEX];
	Vref = 1.2 / Vref;
	temperature = AdcValue[MOS_TEMP_CHL];
	temperature = Vref * temperature;	
#endif
	
	uint8_t index = 0xFF;
	uint16_t temp = BSP_ReadADCVal(MOS_TEMP_CHL);
	
	for (index = 0; index < TEMP_TABLES_LENGTH; index++)
	{
		if(temp <= NTC10K3950[index])
			break;
	}
	return index;
}

/**
 * @brief  APP_ReadWaterTemperature.
 * @note   None.
 * @param  None.
 * @retval Temperature.
 */
uint8_t APP_ReadFetTemperature(void)
{
	return s_stFetTcb.ucTemperature;
}

/**
* @brief  APP_WriteFetTemperatrueTH.
* @note   None.
* @param  val.
* @retval None.
*/
void APP_WriteFetTemperatrueTH(uint8_t val)
{
	s_stFetTcb.ucTemperatureTH = val;
}

/**
* @brief  APP_WriteWaterOverTemperaturePROT.
* @note   None.
* @param  state.
* @retval None.
*/
void APP_WriteFetOverTemperaturePROT(bool state)
{
	s_stFetTcb.bOverTempProtect = state;
}


/**
 * @brief  APP_IsFetTemperatureOver.
 * @note   None.
 * @param  None.
 * @retval true/false.
 */
bool APP_IsFetTemperatureOver(void)
{
	if (s_stFetTcb.ucTemperature > s_stFetTcb.ucTemperatureTH)
		return true;
	else
		return false;
}

