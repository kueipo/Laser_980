
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"

/* Configuration table -------------------------------------------------------*/
BSP_LASER_CONFIG const s_stLaserCfg = 
{
	.htim = LD_TIM,
	/******** POWER ***********/	
	.power = 
	{
		.GpioPort = LD_POWER_PORT,
		.GpioPin = LD_POWER_PIN,
		.ActiveLogic = LD_POWER_LOGIC,
	},
};

/**
 * @brief  BSP_Laser_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Laser_Init(void)
{
	BSP_Laser_Enable(false);
}

/**
 * @brief  BSP_Laser_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Laser_DeInit(void)
{
}

// -----------------------------------------------------------------------------
/**
 * @brief  BSP_Laser_Enable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Laser_Enable(bool bstate)
{
	GPIO_TypeDef *GpioPort;
	uint16_t GpioPin;
	GPIO_PinState PinState;

	GpioPort = s_stLaserCfg.power.GpioPort;
	GpioPin = s_stLaserCfg.power.GpioPin;
	PinState = s_stLaserCfg.power.ActiveLogic;
	
	/*Configure GPIO pin Output Level */
	if (bstate)
		BSP_Digital_Write(GpioPort, GpioPin, PinState);
	else
		BSP_Digital_Write(GpioPort, GpioPin, (GPIO_PinState)(1 - PinState));
}

// -----------------------------------------------------------------------------
/**
 * @brief  BSP_Laser_TimEnable.
 * @note   None.
 * @param  bstate.
 * @retval None.
 */
void BSP_Laser_TimEnable(bool bstate)
{
	TIM_HandleTypeDef *htim = s_stLaserCfg.htim;
	
	if (bstate)	
	{
		/* Enable the TIM Update interrupt */
		__HAL_TIM_SET_COUNTER(htim, 0);
		/* Enable the TIM */
		__HAL_TIM_ENABLE(htim);
	}
	else
		__HAL_TIM_DISABLE(htim);
}

// -----------------------------------------------------------------------------
/**
 * @brief  BSP_Laser_TimSet.
 * @note   None.
 * @param  period(unit:ms).
 * @retval None.
 */
void BSP_Laser_TimSet(uint16_t period)
{
	TIM_HandleTypeDef *htim;
	
	htim = s_stLaserCfg.htim;
	
	__HAL_TIM_DISABLE(htim);
	__HAL_TIM_SET_AUTORELOAD(htim, period);
}

// -----------------------------------------------------------------------------
/**
 * @brief  BSP_Laser_AdcWDGSet.
 * @note   None.
 * @param  high, low.
 * @retval None.
 */
void BSP_Laser_AdcWDGSet(uint16_t high, uint16_t low)
{
	ADC_AnalogWDGConfTypeDef AnalogWDGConfig = {0};
	  
	/** Configure the analog watchdog
	*/
	if (high > 0xFFF || low >= high)
		return;
	
	AnalogWDGConfig.WatchdogMode = ADC_ANALOGWATCHDOG_SINGLE_REG;
	AnalogWDGConfig.Channel = LD_ADC_CHNL;
	AnalogWDGConfig.ITMode = ENABLE;
	AnalogWDGConfig.HighThreshold = high;
	AnalogWDGConfig.LowThreshold = low;
	
	/* stop */
	BSP_Adc_Disable();
	
	if (HAL_ADC_AnalogWDGConfig(&hadc, &AnalogWDGConfig) != HAL_OK)
	{
		Error_Handler();
	}
	
	/* start */
	BSP_Adc_Enable();
}
