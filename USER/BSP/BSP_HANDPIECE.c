
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"

/* Configuration table -------------------------------------------------------*/
const BSP_GPIO_CONFIG s_stHandpieceCfg[HANDPIECE_ID_MAX] = 
{
	/* Handpiece_0 -------------------------------------------------------------*/
  {
    .GpioPort    = HANDPIECE_0_PORT,
    .GpioPin     = HANDPIECE_0_PIN,
    .ActiveLogic = GPIO_PIN_SET,
  },
};

/**
 * @brief  BSP_Handpiece_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Handpiece_Init(void)
{
}

/**
 * @brief  BSP_ReadHandpieceValue.
 * @note   None.
 * @param  id.
 * @retval 0xFF:ERROR.
 *		     0:DISCONN.
 *		     1:CONN.
 */
uint8_t BSP_ReadHandpieceValue(uint8_t id)
{
	GPIO_TypeDef *GpioPort;   
  uint32_t GpioPin; 
  GPIO_PinState ActiveLogic;
	
  if (id >= HANDPIECE_ID_MAX)
    return 0xFF;
	
	GpioPort = s_stHandpieceCfg[id].GpioPort;
	GpioPin  = s_stHandpieceCfg[id].GpioPin;
	ActiveLogic = s_stHandpieceCfg[id].ActiveLogic;
	
	return (ActiveLogic == HAL_GPIO_ReadPin(GpioPort, GpioPin)); 
}
