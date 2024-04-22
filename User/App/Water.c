#include "Water.h"
#include "DEV_Config.h"
/**
* Macro Definition
*/

/* =========================================================================== */
/**
* Function Ceclaration
*/

/* =========================================================================== */
/**
* Variable Definition
*/
//typedef struct {
//	uint8_t Temperature;
//	uint16_t Speed;
//} WaterModel_TypeDef;
//WaterModel_TypeDef WaterModule;

/* =========================================================================== */
/**
* Function Definition
*/

/**
* @brief  Water_Init.
* @note   None.
* @param  None.
* @retval None.
*/
void Water_Init(void)
{
	;
}

/**
* @brief  Water_Run.
* @note   None.
* @param  None.
* @retval None.
*/
void Water_Run(void)
{
	;
}

/**
* @brief  Water_PumpControl.
* @note   None.
* @param  None.
* @retval None.
*/
void Water_PumpControl(bool state)
{
//	switch(state)
//	{
//		case 1:
//			DEV_PUMP_CONTROL(DEV_PUMP_ON);
//		break;
//		default:
//		case 0:
//			DEV_PUMP_CONTROL(DEV_PUMP_OFF);
//		break;
//	}
}

/**
* @brief  Write the temperature of the water.
* @note   None.
* @param  None.
* @retval None.
*/
void Water_TemperatureWrite(uint8_t val)
{
//	WaterModule.Temperature = val;
}

/**
* @brief  Read the temperature of the water.
* @note   None.
* @param  None.
* @retval None.
*/
uint8_t Water_TemperatureRead(void)
{
//	return WaterModule.Temperature;
	return 0;
}

/**
* @brief  Write the flow speed of water.
* @note   None.
* @param  None.
* @retval None.
*/
void Water_SpeedWrite(uint16_t val)
{
//	WaterModule.Speed = val;
}

/**
* @brief  Read the flow speed of water.
* @note   None.
* @param  None.
* @retval None.
*/
uint16_t Water_SpeedRead(void)
{
//	return WaterModule.Speed;
	return 0;
}

/**
* @brief  Water_LevelWrite.
* @note   None.
* @param  None.
* @retval None.
*/
#if 0
void Water_LevelWrite(uint8_t val)
{
	WaterModule.Level = val;
}
#endif

/**
* @brief  Water_LevelRead.
* @note   None.
* @param  None.
* @retval None.
*/
#if 0
uint8_t Water_LevelRead(void)
{
	return WaterModule.Level;
}
#endif
