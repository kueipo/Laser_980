
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Private variables ---------------------------------------------------------*/
__IOM Mos_Struct s_stMosTcb;

/* Private function prototypes -----------------------------------------------*/
static uint8_t MosTemperature_Detection(void);

/* Code ----------------------------------------------------------------------*/
/**
 * @brief  APP_Mos_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Mos_Init(void)
{
	memset((uint8_t *)&s_stMosTcb, 0, sizeof(s_stMosTcb));

	s_stMosTcb.ucTemperature = 0;
	s_stMosTcb.ucTemperatureTH = 45;
	s_stMosTcb.bOverTempProtect = true;
}

/**
 * @brief  APP_Mos_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Mos_Task(void)
{
	s_stMosTcb.ucTemperature = MosTemperature_Detection();
}

/**
 * @brief  MosTemperature_Detection.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static uint8_t MosTemperature_Detection(void)
{
#if 0
	Vref = AdcValue[ADC_VREF_INDEX];
	Vref = 1.2 / Vref;
	temperature = AdcValue[MOS_TEMP_CHL];
	temperature = Vref * temperature;	
#endif
	
	static uint16_t Data[4] = {0};
	uint8_t index = 0xFF;
	uint16_t temp = BSP_ReadADCVal(MOS_TEMP_CHL);
	temp = MiddleAverageValueFilter(temp, Data, 4);
	
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
uint8_t APP_ReadMosTemperature(void)
{
	return s_stMosTcb.ucTemperature;
}

/**
* @brief  APP_WriteMosTemperatrueTH.
* @note   None.
* @param  val.
* @retval None.
*/
void APP_WriteMosTemperatrueTH(uint8_t val)
{
	s_stMosTcb.ucTemperatureTH = val;
}

/**
* @brief  APP_WriteWaterOverTemperaturePROT.
* @note   None.
* @param  state.
* @retval None.
*/
void APP_WriteMosOverTemperaturePROT(bool state)
{
	s_stMosTcb.bOverTempProtect = state;
}


/**
 * @brief  APP_IsMosTemperatureOver.
 * @note   None.
 * @param  None.
 * @retval true/false.
 */
bool APP_IsMosTemperatureOver(void)
{
	if (s_stMosTcb.ucTemperature > s_stMosTcb.ucTemperatureTH)
		return true;
	else
		return false;
}

