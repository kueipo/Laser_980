
/* Includes ------------------------------------------------------------------*/
#include "BSP/BSP_Common.h"
								   
/* Configuration table -------------------------------------------------------*/                                     
const BSP_GPIO_CONFIG s_stBuzzerCfg[BUZZER_ID_MAX] = 
{
	/*******BUZZER_0***********/
	{
		.GpioPort    = BUZZER_0_PORT,
		.GpioPin     = BUZZER_0_PIN,
		.ActiveLogic = GPIO_PIN_SET,
	},
};

/**
 * @brief  BSP_Pump_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Buzzer_Init(void)
{
//	BSP_Buzzer_Operate(0, BUZZER_OFF);
}

/**
 * @brief  BSP_Buzzer_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Buzzer_DeInit(void)
{
	GPIO_TypeDef *GpioPort;
	uint32_t GpioPin;

	for (uint8_t index = 0; index < BUZZER_ID_MAX; index++)
	{
		GpioPort = s_stBuzzerCfg[index].GpioPort;
		GpioPin = s_stBuzzerCfg[index].GpioPin;

		HAL_GPIO_DeInit(GpioPort, GpioPin);
	}
}

/**
 * @brief  BSP_Buzzer_Operate.
 * @note   None.
 * @param  BuzzerId.
 *		     BuzzerOpMode:
 *					 BUZZER_OFF;
 *					 BUZZER_ON;
 * @retval bool.
 */
bool BSP_Buzzer_Operate(uint8_t id, uint8_t mode)
{
	GPIO_TypeDef *GpioPort;
	uint16_t GpioPin;
	GPIO_PinState PinState;

	if (id >= BUZZER_ID_MAX)
		return false;

	GpioPort = s_stBuzzerCfg[id].GpioPort;
	GpioPin = s_stBuzzerCfg[id].GpioPin;
	PinState = s_stBuzzerCfg[id].ActiveLogic;

	switch (mode)
	{
	case BUZZER_OFF:
		BSP_Digital_Write(GpioPort, GpioPin, (GPIO_PinState)(1 - PinState));
		break;
	case BUZZER_ON:
		BSP_Digital_Write(GpioPort, GpioPin, PinState);
		break;
	default:
		return false;
	}
	return true;
}
