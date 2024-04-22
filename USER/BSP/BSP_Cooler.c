
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"
								   
/* Configuration table -------------------------------------------------------*/
const BSP_COOLER_CONFIG s_stCoolerCfg[COOLER_ID_MAX] = {
	/******* COOLER_0 ***********/
	{
		.htim = &htim8,
		.Channel = TIM_CHANNEL_1,
	},
};

/**
 * @brief  BSP_Cooler_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Cooler_Init(void)
{
}

/**
 * @brief  BSP_Cooler_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Cooler_DeInit(void)
{
}

/**
 * @brief  BSP_Cooler_Operate.
 * @note   None.
 * @param  CoolerId;
 * @param  CoolerOpMode:
 * @param  COOLER_OFF:
 * @param  COOLER_ON:
 * @retval bool.
 */
bool BSP_Cooler_Operate(uint8_t CoolerId, uint8_t CoolerOpMode)
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;

	if (CoolerId >= COOLER_ID_MAX)
		return false;

	htim = s_stCoolerCfg[CoolerId].htim;
	Channel = s_stCoolerCfg[CoolerId].Channel;

	switch (CoolerOpMode)
	{
	default:
	case COOLER_OFF:
		/* Check the TIM complementary channel state */
		if (TIM_CHANNEL_N_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
			HAL_TIMEx_PWMN_Stop(htim, Channel);
		break;
	case COOLER_ON:
		/* Check the TIM complementary channel state */
		if (TIM_CHANNEL_N_STATE_GET(htim, Channel) == HAL_TIM_CHANNEL_STATE_READY)
			HAL_TIMEx_PWMN_Start(htim, Channel);
		break;
	}
	return true;
}

/**
 * @brief  BSP_Cooler_Config.
 * @note   None.
 * @param  CoolerId, uiPwmOut.
 * @retval None.
 */
bool BSP_Cooler_Config(uint8_t CoolerId, uint16_t uiPwmOut)
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;

	if (CoolerId >= COOLER_ID_MAX)
		return false;

	htim = s_stCoolerCfg[CoolerId].htim;
	Channel = s_stCoolerCfg[CoolerId].Channel;

	__HAL_TIM_SET_COMPARE(htim, Channel, uiPwmOut);

	return true;
}
