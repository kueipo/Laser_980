
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"

/* Configuration table -------------------------------------------------------*/
const BSP_GPIO_CONFIG s_stLockCfg[LOCKER_ID_MAX] = 
{
	/*******Locker_0***********/
	{
		.GpioPort    = SAFELOCKER_0_GPIO_Port,
		.GpioPin     = SAFELOCKER_0_Pin,
		.ActiveLogic = GPIO_PIN_RESET,
	},
};

/**
 * @brief  BSP_SafeLocker_Init.
 * @note   None.
 * @param  None.
 * @retval None
 */
void BSP_SafeLocker_Init(void)
{
}

/**
 * @brief  BSP_SafeLocker_DeInit.
 * @note   None.
 * @param  id.
 * @retval None.
 */
void BSP_SafeLocker_DeInit(void)
{
	GPIO_TypeDef *GpioPort;   
	uint32_t GpioPin; 
	uint8_t index;
    
	for (index = 0; index < LOCKER_ID_MAX; index++)
	{
		GpioPort = s_stLockCfg[index].GpioPort;
		GpioPin = s_stLockCfg[index].GpioPin;
		
		HAL_GPIO_DeInit(GpioPort, GpioPin);
	} 
}

/**
 * @brief  BSP_SafeLockerValue.
 * @note   None.
 * @param  id.
 * @retval 0xFF:error.
 *		     0:CONN.
 *		     1:DISCONN.
 */
uint8_t BSP_SafeLockerValue(uint8_t id)
{
	GPIO_TypeDef *GpioPort;   
  uint32_t GpioPin; 
  GPIO_PinState ActiveLogic;
	
  if (id >= LOCKER_ID_MAX)
		return 0xFF;
	
	GpioPort = s_stLockCfg[id].GpioPort;
	GpioPin  = s_stLockCfg[id].GpioPin;
	ActiveLogic = s_stLockCfg[id].ActiveLogic;
	
  return (ActiveLogic == HAL_GPIO_ReadPin(GpioPort, GpioPin)); 
}
