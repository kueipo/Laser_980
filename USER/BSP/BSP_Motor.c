
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"
								   
#define SPEED_LENGTH		3

uint16_t SpeedVal[MOTOR_ID_MAX][SPEED_LENGTH];

/* Configuration table -------------------------------------------------------*/
BSP_GPIO_CONFIG const s_stWaterLevelCfg[MOTOR_ID_MAX] = 
{
	/*******High Level***********/
	{
		.GpioPort    = MOTOR_0_PORT,
		.GpioPin     = MOTOR_0_PIN,
		.ActiveLogic = GPIO_PIN_RESET,
	},
	
	/*******Low Level***********/
	{
		.GpioPort    = MOTOR_1_PORT,
		.GpioPin     = MOTOR_1_PIN,
		.ActiveLogic = GPIO_PIN_RESET,
	},
};


void BSP_Motor_Init(void)
{
	/* Disables a device specific interrupt in the NVIC interrupt controller. */
	HAL_NVIC_DisableIRQ(BSP_MOTOR_0_DMA_CHNL_IRQn);
	/* Starts the TIM Input Capture measurement in DMA mode */
	HAL_TIM_IC_Start_DMA(BSP_MOTOR_0_DETECTION_TIMX, BSP_MOTOR_0_DETECTION_CHNL, (uint32_t*)(&SpeedVal[MOTOR_0][0]), SPEED_LENGTH);
	
	/* Disables a device specific interrupt in the NVIC interrupt controller. */
	HAL_NVIC_DisableIRQ(BSP_MOTOR_1_DMA_CHNL_IRQn);
	/* Starts the TIM Input Capture measurement in DMA mode */
	HAL_TIM_IC_Start_DMA(BSP_MOTOR_1_DETECTION_TIMX, BSP_MOTOR_1_DETECTION_CHNL, (uint32_t*)(&SpeedVal[MOTOR_1][0]), SPEED_LENGTH);
	

}

//void BSP_Motor_DeInit(void)
//{
//}

/**
 * @brief  BSP_ReadWaterSpeed.
 * @note   None.
 * @param  None.
 * @retval FlowSpeed.
 */
uint16_t BSP_Motor_ReadSpeed(uint8_t id)
{
	uint16_t data[SPEED_LENGTH] = {0};
	uint16_t average = 0;
	uint8_t index;
	uint8_t location;
	uint16_t channel;
	TIM_HandleTypeDef *pTim;
	switch (id)
	{
	case MOTOR_0:
		pTim = BSP_MOTOR_0_DETECTION_TIMX;
		channel = TIM_DMA_ID_CC1;
		break;
	case MOTOR_1:
		pTim = BSP_MOTOR_1_DETECTION_TIMX;
		channel = TIM_DMA_ID_CC1;
		break;
	default:
		return 0xFFFF;
	}

	location = SPEED_LENGTH - __HAL_DMA_GET_COUNTER(pTim->hdma[channel]);

	for (index = 0; index < SPEED_LENGTH; index++)
	{
		data[index] = SpeedVal[id][(index + location) % SPEED_LENGTH];
	}
		
	for (index = 0; index < (SPEED_LENGTH - 1); index++)
	{
		if (data[index + 1] < data[index])
		{
			data[index + 1] += 30000;	/* TIM 30000 */
		}
		average += (data[index + 1] - data[index]);
	}
	average = average >> 1;
		
	/*	SystemData.FanSpeed[0] = 72000000/720/avg */
//	if (average >= 10)
//	{
//		average = (100000 / average);
//	}
//	else
//	{
//		average = 0;
//	}
	
	for (index = 0; index < SPEED_LENGTH; index++)
	{
//		SpeedVal[id][index] = 0;
	}
	
	return average;
}

/**
 * @brief  BSP_Motor_WriteState.
 * @note   None.
 * @param  id.
 * @param  state.
 * @retval true/false.
 */
bool BSP_Motor_WriteState(uint8_t id, bool state)
{
	GPIO_TypeDef *GpioPort;
	uint32_t GpioPin;
	GPIO_PinState ActiveLogic;
	
    if (id >= MOTOR_ID_MAX)
        return false;
	
	GpioPort = s_stWaterLevelCfg[id].GpioPort;
	GpioPin  = s_stWaterLevelCfg[id].GpioPin;
	ActiveLogic = s_stWaterLevelCfg[id].ActiveLogic;
	
	if (state == false)
	{
		ActiveLogic = (GPIO_PinState)(1 - ActiveLogic);
	}
	
	HAL_GPIO_WritePin(GpioPort, GpioPin, ActiveLogic);
	
	return true;
}

//bool BSP_Motor_ReadState(uint8_t id)
//{
//	GPIO_TypeDef	*GpioPort;
//    uint32_t		GpioPin;
//	GPIO_PinState 	ActiveLogic;
//	
//	if (id >= MOTOR_ID_MAX)
//        return false;
//		
//	GpioPort = s_stWaterLevelCfg[id].GpioPort;
//	GpioPin  = s_stWaterLevelCfg[id].GpioPin;
//	ActiveLogic = s_stWaterLevelCfg[id].ActiveLogic;
//	
//	return (ActiveLogic == HAL_GPIO_ReadPin(GpioPort, GpioPin)); 
//}
