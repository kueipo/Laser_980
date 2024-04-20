
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"

/* Configuration table -------------------------------------------------------*/
const BSP_GPIO_CONFIG s_stKeyCfg[KEY_ID_MAX] = 
{
  /*******KEY_0***********/
  {
    .GpioPort    = KEY_0_PORT,
    .GpioPin     = KEY_0_PIN,
    .ActiveLogic = GPIO_PIN_RESET,
  },
	
	/*******KEY_1***********/
  {
    .GpioPort    = KEY_1_PORT,
    .GpioPin     = KEY_1_PIN,
    .ActiveLogic = GPIO_PIN_RESET,
  },
};

/**
 * @brief  BSP_Key_Init.
 * @note   None.
 * @param  None.
 * @retval None
 */
void BSP_Key_Init(void)
{	
}

/**
 * @brief  BSP_Key_DeInit.
 * @note   None.
 * @param  None.
 * @retval None
 */
void BSP_Key_DeInit(void)
{
	GPIO_TypeDef *GpioPort;
  uint32_t GpioPin;
  uint8_t index;
    
  for (index = 0; index < KEY_ID_MAX; index++)
  {
		GpioPort = s_stKeyCfg[index].GpioPort;
		GpioPin = s_stKeyCfg[index].GpioPin;
		
    HAL_GPIO_DeInit(GpioPort, GpioPin);  
  } 
}

/**
 * @brief  BSP_ReadKeyValue.
 * @note   None.
 * @param  id.
 * @retval 0xFF:error.
 *		  	 0:RELEASE.
 *		 		 1:PUSH.
 */
uint8_t BSP_ReadKeyValue(uint8_t id)
{
	GPIO_TypeDef *GpioPort;   
  uint32_t GpioPin; 
  GPIO_PinState ActiveLogic;
	
  if (id >= KEY_ID_MAX)
    return 0xFF;
	
	GpioPort = s_stKeyCfg[id].GpioPort;
	GpioPin  = s_stKeyCfg[id].GpioPin;
	ActiveLogic = s_stKeyCfg[id].ActiveLogic;
	
	return (ActiveLogic == HAL_GPIO_ReadPin(GpioPort, GpioPin)); 
}
