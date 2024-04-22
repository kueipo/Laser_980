
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"
					   
/* Configuration table -------------------------------------------------------*/
#ifdef USING_LED_TIMER
const BSP_LED_CONFIG g_stLedCfg[LED_ID_MAX] =
#else
const BSP_GPIO_CONFIG g_stLedCfg[LED_ID_MAX] = 
#endif
{
	/******* LED_0 ***********/
	{
#ifdef USING_LED_TIMER
		.htim = &htim1,
		.Channel = TIM_CHANNEL_1,
#else
		.GpioPort = LED_R_PORT,
		.GpioPin = LED_R_PIN,
		.OutputLogic = GPIO_PIN_SET, /* Default LED OFF*/
#endif
	},
	/******* LED_1 ***********/
	{
#ifdef USING_LED_TIMER
		.htim = &htim1,
		.Channel = TIM_CHANNEL_1,
#else
		.GpioPort = LED_B_PORT,
		.GpioPin = LED_B_PIN,
		.OutputLogic = GPIO_PIN_SET, /* Default LED OFF*/
#endif
	},
	/******* LED_2 ***********/

};

/**
 * @brief  BSP_Led_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Led_Init(void)
{
	for (uint8_t index = 0; index < LED_ID_MAX; index++)
	{
		BSP_Led_Operate(index, LED_OFF);
	}
}

/**
 * @brief  BSP_Led_Operate.
 * @note   None.
 * @param  LedId;
 *		  LedOpMode:
 *					LED_HOLD:
 *					LED_ON:
 *					LED_OFF:
 *					LED_TOGGLE:
 * @retval None.
 */
void BSP_Led_Operate(uint8_t LedId, uint8_t LedOpMode)
{
#ifdef USING_LED_TIMER
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
#else
	GPIO_TypeDef *GPIOx;
	uint32_t GPIO_Pin;
	GPIO_PinState PinState;
#endif

	if (LedId >= LED_ID_MAX)
		return;

#ifdef USING_LED_TIMER
	htim = g_stLedCfg[LedId].htim;
	Channel = g_stLedCfg[LedId].Channel;
#else
	GPIOx = g_stLedCfg[LedId].GpioPort;
	GPIO_Pin = g_stLedCfg[LedId].GpioPin;
	PinState = g_stLedCfg[LedId].OutputLogic;
#endif

	switch (LedOpMode)
	{
	case LED_OFF:
#ifdef USING_LED_TIMER
/* Check the TIM complementary channel state */
#if 0
		if (TIM_CHANNEL_N_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
		{
			HAL_TIMEx_PWMN_Stop(htim, Channel);	
		}
#else
		if (TIM_CHANNEL_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
		{
			HAL_TIM_PWM_Stop(htim, Channel);
		}
#endif
#else
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, (GPIO_PinState)(1 - PinState));
#endif
		break;
	case LED_ON:
#ifdef USING_LED_TIMER
#if 0
		if (TIM_CHANNEL_N_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
		{
			HAL_TIMEx_PWMN_Start(htim, Channel);
		}
#else
		/* Check the TIM complementary channel state */
		if (TIM_CHANNEL_STATE_GET(htim, Channel) == HAL_TIM_CHANNEL_STATE_READY)
		{
			HAL_TIM_PWM_Start(htim, Channel);
		}
#endif
#else
		HAL_GPIO_WritePin(GPIOx, GPIO_Pin, PinState);
#endif
		break;
	case LED_TOGGLE:
#ifdef USING_LED_TIMER
#if 0
		if (TIM_CHANNEL_N_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
		{
			HAL_TIMEx_PWMN_Start(htim, Channel);
		}
		else
		{
			HAL_TIMEx_PWMN_Stop(htim, Channel);
		}
#else
		if (TIM_CHANNEL_STATE_GET(htim, Channel) == HAL_TIM_CHANNEL_STATE_READY)
		{
			HAL_TIM_PWM_Start(htim, Channel);
		}
		else
		{
			HAL_TIM_PWM_Stop(htim, Channel);
		}
#endif
#else
		HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);
#endif
		break;
	case LED_HOLD:
		break;
	default:
		break;
	}
}

/**
 * @brief  BSP_Led_Config.
 * @note   None.
 * @param  LedId, uiPwmOut.
 * @retval None.
 */
void BSP_Led_Config(uint8_t LedId, uint16_t uiPwmOut)
{
#ifdef USING_LED_TIMER
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
#else

#endif
	if (LedId >= LED_ID_MAX)
		return;

#ifdef USING_LED_TIMER
	htim = g_stLedCfg[LedId].htim;
	Channel = g_stLedCfg[LedId].Channel;
	__HAL_TIM_SET_COMPARE(htim, Channel, uiPwmOut);
/*	__HAL_TIM_SET_AUTORELOAD(htim, Period); */
#else

#endif
}
