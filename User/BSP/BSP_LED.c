
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"
								   
/* Configuration table -------------------------------------------------------*/
const BSP_LED_CONFIG g_stLedCfg[LED_ID_MAX] = 
{
  /******* LED_0 ***********/
  {
		.htim = &htim8,
		.Channel = TIM_CHANNEL_3,
  },
	/******* LED_1 ***********/
  {
		.htim = &htim8,
		.Channel = TIM_CHANNEL_4,
  },
	/******* LED_2 ***********/
  {
		.htim = &htim8,
		.Channel = TIM_CHANNEL_2,
  },
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
		BSP_Led_Operate(index, LED_OFF);
}

/**
 * @brief  BSP_Led_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Led_DeInit(void)
{
}

/**
 * @brief  BSP_Led_Operate.
 * @note   None.
 * @param  id;
 *		   		mode:
 *					LED_HOLD:
 *					LED_ON:
 *					LED_OFF:
 *					LED_TOGGLE:
 * @retval None.
 */
void BSP_Led_Operate(uint8_t id, uint8_t mode)
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;

	if (id >= LED_ID_MAX)
		return;

	htim = g_stLedCfg[id].htim;
	Channel = g_stLedCfg[id].Channel;

	switch (mode)
	{
	case LED_OFF:
		/* Check the TIM complementary channel state */
#if 0
			if (TIM_CHANNEL_N_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
				HAL_TIMEx_PWMN_Stop(htim, Channel);
#else
		if (TIM_CHANNEL_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
			HAL_TIM_PWM_Stop(htim, Channel);
#endif
		break;

	case LED_ON:
		/* Check the TIM complementary channel state */
#if 0
			if (TIM_CHANNEL_N_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
				HAL_TIMEx_PWMN_Start(htim, Channel);
#else
		if (TIM_CHANNEL_STATE_GET(htim, Channel) == HAL_TIM_CHANNEL_STATE_READY)
			HAL_TIM_PWM_Start(htim, Channel);
#endif
		break;

	case LED_TOGGLE:
#if 0
			if (TIM_CHANNEL_N_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
				HAL_TIMEx_PWMN_Start(htim, Channel);
			else
				HAL_TIMEx_PWMN_Stop(htim, Channel);
#else
		if (TIM_CHANNEL_STATE_GET(htim, Channel) == HAL_TIM_CHANNEL_STATE_READY)
			HAL_TIM_PWM_Start(htim, Channel);
		else
			HAL_TIM_PWM_Stop(htim, Channel);
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
 * @param  id, uiPwmOut.
 * @retval None.
 */
void BSP_Led_Config(uint8_t id, uint16_t pwmout)
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;

	if (id >= LED_ID_MAX)
		return;

	htim = g_stLedCfg[id].htim;
	Channel = g_stLedCfg[id].Channel;
	
	/* Set duty cycle */
	__HAL_TIM_SET_COMPARE(htim, Channel, pwmout);
	/* Set period  */
	/*	__HAL_TIM_SET_AUTORELOAD(htim, Period); */
}
