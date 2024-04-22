
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"

/*
	DAC �����ѹ = VREF+ * ( DOR / 4095 )
*/
/* Configuration table -------------------------------------------------------*/
const BSP_POWER_CONFIG s_stPowerCfg = 
{
	.MaxVal	= 4096-1,
	.V11	= 1365,			/* (1.1V/3.3V) * 4095 */
	.hdac	= &hdac,
	.Channel = DAC_CHANNEL_2,
};

/**
 * @brief  BSP_Power_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Power_Init(void)
{
	DAC_HandleTypeDef  	*hdac;
	uint32_t 			Channel;
	
    hdac = s_stPowerCfg.hdac;
    Channel	= s_stPowerCfg.Channel;
	
	BSP_Power_Config(0);
	
	HAL_DAC_Start(hdac, Channel);
}

/**
 * @brief  BSP_Power_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Power_DeInit(void)
{
}

/**
 * @brief  BSP_Power_Enable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Power_Enable(void)
{
	DAC_HandleTypeDef  	*hdac;
	uint32_t 			Channel;
	
    hdac = s_stPowerCfg.hdac;
    Channel	= s_stPowerCfg.Channel;
	
	HAL_DAC_Start(hdac, Channel);
}

/**
 * @brief  BSP_Power_Disable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Power_Disable(void)
{
	DAC_HandleTypeDef  	*hdac;
	uint32_t 			Channel;
	
    hdac 	= s_stPowerCfg.hdac;
    Channel	= s_stPowerCfg.Channel;
	
	HAL_DAC_Stop(hdac, Channel);
}

/**
 * @brief  BSP_Power_Config.
 * @note   None.
 * @param  val.
 * @retval None.
 */
void BSP_Power_Config(uint16_t usVal)
{
	uint16_t 			MaxVal;
	DAC_HandleTypeDef  	*hdac;
	uint32_t 			Channel;
		
	MaxVal 	= s_stPowerCfg.MaxVal;
    hdac 	= s_stPowerCfg.hdac;
    Channel	= s_stPowerCfg.Channel;
	
	if (usVal > MaxVal)
		usVal = MaxVal;
	
	/* No modification required */
	if (HAL_DAC_GetValue(hdac, Channel) != (uint32_t)usVal)
		/* Write, refresh */
		HAL_DAC_SetValue(hdac, Channel, DAC_ALIGN_12B_R, (uint32_t)usVal);
}
