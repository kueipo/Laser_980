
/* Includes ------------------------------------------------------------------*/
#include "BSP/BSP_Common.h"
								   
/* Configuration table -------------------------------------------------------*/
typedef struct
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
} TIM_Def;

typedef struct
{
	TIM_Def tim;
} Buzzer_Def;
	
const Buzzer_Def s_stBuzzerCfg[BUZZER_ID_MAX] = 
{
	{
		.tim = 
		{
			.htim = BUZZER_0_TIM,
			.Channel = BUZZER_0_CHANNEL,
		},
	},
};

/**
 * @brief  BSP_Buzzer_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Buzzer_Init(void)
{
#if 0	/* disable One pulse mode and disable Trigger mode */
	__BSP_TIM_OPM_DISABLE(htim);
	__BSP_TIM_TRIGGER_DISABLE(htim);
#endif
	
	BSP_Buzzer_Operate(BUZZER_0, BUZZER_ON);
}

/**
 * @brief  BSP_Buzzer_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Buzzer_DeInit(void)
{
}

/**
 * @brief  BSP_Buzzer_Operate.
 * @note   None.
 * @param  id.
 *		   	 Buzzermode:
 *				 	BUZZER_OFF;
 *				 	BUZZER_ON;
 * @retval bool.
 */
bool BSP_Buzzer_Operate(uint8_t id, uint8_t mode)
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;

	UNUSED(mode);

	htim = s_stBuzzerCfg[id].tim.htim;
	Channel = s_stBuzzerCfg[id].tim.Channel;

#if 0	/* disable One pulse mode and disable Trigger mode */
	__BSP_TIM_OPM_DISABLE(htim);
	__BSP_TIM_TRIGGER_DISABLE(htim);
#endif

#if 0
	HAL_TIM_PWM_Start(htim, Channel);
#else
	HAL_TIMEx_PWMN_Start(htim, Channel);
#endif

	return true;
}
