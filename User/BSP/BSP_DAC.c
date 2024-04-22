
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"

/*
 *	DAC = VREF+ * ( DOR / 4095 )
 */
/* Configuration table -------------------------------------------------------*/
const BSP_DAC_CONFIG s_stPowerCfg[DAC_ID_MAX] = 
{
	{
		.MaxVal	= 0XFFFF,
		.hdac	= &hdac,
		.Channel = DAC_CHANNEL_1,
	},
	{
		.MaxVal	= 0xFFFF,
		.hdac	= &hdac,
		.Channel = DAC_CHANNEL_2,
	},
};

/**
 * @brief  BSP_DAC_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_DAC_Init(void)
{
	DAC_HandleTypeDef *hdac;
	uint32_t Channel;

	for (uint8_t index = 0; index < DAC_ID_MAX; index++)
	{
		hdac = s_stPowerCfg[index].hdac;
		Channel	= s_stPowerCfg[index].Channel;
		
		BSP_DAC_Config(index, 0);
		HAL_DAC_Start(hdac, Channel);
	}
}

/**
 * @brief  BSP_DAC_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_DAC_DeInit(void)
{
}

/**
 * @brief  BSP_DAC_Enable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_DAC_Enable(uint8_t id)
{
	DAC_HandleTypeDef *hdac;
	uint32_t Channel;
	
	if (id > DAC_ID_MAX)
		return;

	hdac = s_stPowerCfg[id].hdac;
  Channel	= s_stPowerCfg[id].Channel;
	
	HAL_DAC_Start(hdac, Channel);
}

/**
 * @brief  BSP_DAC_Disable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_DAC_Disable(uint8_t id)
{
	DAC_HandleTypeDef *hdac;
	uint32_t Channel;

	if (id > DAC_ID_MAX)
		return;

  hdac 	= s_stPowerCfg[id].hdac;
  Channel	= s_stPowerCfg[id].Channel;

	HAL_DAC_Stop(hdac, Channel);
}

/**
 * @brief  BSP_DAC_Config.
 * @note   None.
 * @param  val.
 * @retval None.
 */
void BSP_DAC_Config(uint8_t id, uint16_t usVal)
{
	uint16_t MaxVal;
	DAC_HandleTypeDef *hdac;
	uint32_t Channel;
	
	if (id > DAC_ID_MAX)
		return;
	
	MaxVal = s_stPowerCfg[id].MaxVal;
  hdac = s_stPowerCfg[id].hdac;
  Channel	= s_stPowerCfg[id].Channel;
	
	if (usVal > MaxVal)
		usVal = MaxVal;
	
	/* No modification required */
	if (HAL_DAC_GetValue(hdac, Channel) != (uint32_t)usVal)
		/* Write, refresh */
		HAL_DAC_SetValue(hdac, Channel, DAC_ALIGN_12B_R, (uint32_t)usVal);
}
