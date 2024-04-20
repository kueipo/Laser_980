
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"
								   
/* Configuration table -------------------------------------------------------*/                                     
const BSP_GPIO_CONFIG s_stPumpCfg[PUMP_ID_MAX] = 
{
    /*******PUMP_0***********/
    {
        .GpioPort    = PUMP_0_PORT,
        .GpioPin     = PUMP_0_PIN,
        .OutputLogic = GPIO_PIN_RESET,	/* Default PUMP OFF*/
    },   
};

/**
 * @brief  BSP_Pump_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Pump_Init(void)
{
}

/**
 * @brief  BSP_Pump_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Pump_DeInit(void)
{
	GPIO_TypeDef	*GpioPort;
    uint32_t		GpioPin;
    uint8_t 		index;
    
    for (index = 0; index < PUMP_ID_MAX; index++)
    {
		GpioPort = s_stPumpCfg[index].GpioPort;
		GpioPin = s_stPumpCfg[index].GpioPin;
		
        HAL_GPIO_DeInit(GpioPort, GpioPin);  
    } 
}

/**
 * @brief  BSP_Pump_Operate.
 * @note   None.
 * @param  PumpId.
 *		  PumpOpMode:
 *					 PUMP_OFF;
 *					 PUMP_ON;
 * @retval None.
 */
void BSP_Pump_Operate(uint8_t PumpId, uint8_t PumpOpMode)
{
    GPIO_TypeDef* GpioPort;
    uint16_t      GpioPin;
    GPIO_PinState PinState;
        
    if (PumpId >= PUMP_ID_MAX)
        return;
    
    GpioPort = s_stPumpCfg[PumpId].GpioPort;
    GpioPin  = s_stPumpCfg[PumpId].GpioPin;
    PinState = s_stPumpCfg[PumpId].OutputLogic;
	
    switch (PumpOpMode)
    {
		default:
			break;
		case PUMP_OFF:
        {
			BSP_Digital_Write(GpioPort, GpioPin, PinState);
			break;
        }
		
        case PUMP_ON:
        {
            BSP_Digital_Write(GpioPort, GpioPin, (GPIO_PinState)(1 - PinState));
			break;
        }
    }
}
