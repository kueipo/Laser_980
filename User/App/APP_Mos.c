
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Private define ------------------------------------------------------------*/
#define TEMPERATURE_FLAG 					"temp"
#define MIN_TEMPERATURE						30
#define MAX_TEMPERATURE						45
#define TEMPERATURE_PROTECT_FLAG "protect"

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
	
	uint8_t data = 0;
	/* tempterature */
	APP_Common_GetParameters(TEMPERATURE_FLAG, (uint8_t*)&data, sizeof(s_stMosTcb.ucTemperatureTH));
	if (data > MAX_TEMPERATURE || data < MIN_TEMPERATURE)
	{
		APP_Mos_WriteTemperatrueTH(36);
	}
	else
		s_stMosTcb.ucTemperatureTH = data;
	
	/* tempterature protect */
	APP_Common_GetParameters(TEMPERATURE_PROTECT_FLAG, (uint8_t*)&data, sizeof(s_stMosTcb.bOverTempProtect));
	s_stMosTcb.bOverTempProtect = (bool)data;
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
uint8_t APP_Mos_ReadTemperature(void)
{
	return s_stMosTcb.ucTemperature;
}

/**
* @brief  APP_Mos_WriteTemperatrueTH.
* @note   None.
* @param  val.
* @retval None.
*/
void APP_Mos_WriteTemperatrueTH(uint8_t val)
{
	if (s_stMosTcb.ucTemperatureTH == val)
		return;
	
	if (val > MAX_TEMPERATURE || val < MIN_TEMPERATURE)
		return;
	
	s_stMosTcb.ucTemperatureTH = val;
	uint8_t temp = val;
	APP_Common_SaveParameters(TEMPERATURE_FLAG, (uint8_t*)&temp, sizeof(temp));
}

/**
 * @brief  APP_Water_ReadTemperatrueTH.
 * @note   None.
 * @param  None.
 * @retval TemperatureTh.
 */
uint8_t APP_Water_ReadTemperatrueTH(void)
{
	return s_stMosTcb.ucTemperatureTH;
}

/**
* @brief  APP_WriteWaterOverTemperaturePROT.
* @note   None.
* @param  state.
* @retval None.
*/
void APP_Mos_WriteOverTemperaturePROT(bool state)
{
	if (s_stMosTcb.bOverTempProtect == state)
		return;
	
	s_stMosTcb.bOverTempProtect = state;
	uint8_t temp = state;
	APP_Common_SaveParameters(TEMPERATURE_PROTECT_FLAG, (uint8_t*)&temp, sizeof(temp));
}

/**
 * @brief  APP_Mos_ReadOverTemperaturePROT.
 * @note   None.
 * @param  None.
 * @retval bOverTempProtect.
 */
bool APP_Mos_ReadOverTemperaturePROT(void)
{
	return s_stMosTcb.bOverTempProtect;
}

/**
 * @brief  APP_Mos_IsTemperatureOver.
 * @note   None.
 * @param  None.
 * @retval true/false.
 */
bool APP_Mos_IsTemperatureOver(void)
{
	if (s_stMosTcb.ucTemperature > s_stMosTcb.ucTemperatureTH)
		return true;
	else
		return false;
}
