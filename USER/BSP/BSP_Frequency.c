
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"
								   
/* Configuration table -------------------------------------------------------*/
const BSP_FREQUENCY_CONFIG s_stFrequencyCfg = 
{
	.htim = &htim3,
	.Channel = TIM_CHANNEL_1,
};

typedef struct
{
	volatile uint16_t Period;
	volatile uint16_t Pulse;
}Frequency_St;
Frequency_St s_stFrequency = 
{
	.Period = 10000,
	.Pulse = 100,
};

/* Function prototypes -------------------------------------------------------*/
/**
  * @brief  BSP_Frequency_Init.
  * @note   None.
  * @param  None.
  * @retval None.
  */
void BSP_Frequency_Init(void)
{
	BSP_Frenquency_Disable();
}

/**
  * @brief  BSP_Frenquency_DeInit.
  * @note   None.
  * @param  None.
  * @retval None.
  */
void BSP_Frenquency_DeInit(void)
{
}

/**
 * @brief  BSP_Frenquency_Enable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Frenquency_Enable(void)
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	
	uint16_t Pulse;
	uint16_t Period;
	
	htim = s_stFrequencyCfg.htim;
	Channel = s_stFrequencyCfg.Channel;
	
	Pulse = s_stFrequency.Pulse;
	Period = s_stFrequency.Period;
	
	/* Duty cycle */
	__HAL_TIM_SET_COMPARE(htim, Channel, Pulse);
	/* Period */
	__HAL_TIM_SET_AUTORELOAD(htim, Period);
	/* Set the TIM Counter Register value on runtime */
	__HAL_TIM_SET_COUNTER(htim, 0);
	
	htim->Instance->EGR = TIM_EGR_UG; // Trigger update event
//	htim->Instance->EGR = TIM_EGR_CC1G; // Trigger Compare event
		
	if (Pulse < Period)
	{
		/*  Clear the specified TIM interrupt flag */
		__BSP_TIM_CLEAR_CCIT_FLAG(htim, Channel);
		/* Capture/Compare X interrupt */
		__BSP_TIM_ENABLE_CCIT(htim, Channel);
	}
	else
	{
		/* Capture/Compare X interrupt */
		__BSP_TIM_DISABLE_CCIT(htim, Channel);
	}
	
#if 1
	/* Enable the TIM Update interrupt */
	__HAL_TIM_ENABLE_IT(htim, TIM_IT_UPDATE);
#endif

#if 0
	/* Enables the TIM Capture Compare Channel x */
	TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);

	if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
	{
		/* Enable the TIM main Output */
		__HAL_TIM_MOE_ENABLE(htim);
	}
#endif
}

/**
 * @brief  BSP_Frenquency_Disable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Frenquency_Disable(void)
{
	TIM_HandleTypeDef	*htim;
	uint32_t	Channel;
		
	htim = s_stFrequencyCfg.htim;
	Channel  = s_stFrequencyCfg.Channel;
	
	/* Duty cycle */
	__HAL_TIM_SET_COMPARE(htim, Channel, 0);
	/* Capture/Compare X interrupt */
	__BSP_TIM_DISABLE_CCIT(htim, Channel);

#if 1
	/* Disable the TIM Update interrupt */
	__HAL_TIM_DISABLE_IT(htim, TIM_IT_UPDATE);
#endif
}

/**
 * @brief  BSP_Frenquency_Config.
 * @note   None.
 * @param  Period.
 * @param  Pulse.
 * @retval None.
 */
void BSP_Frenquency_Config(uint16_t Period, uint16_t Pulse)
{
	s_stFrequency.Period = Period;
	s_stFrequency.Pulse = Pulse;
}
