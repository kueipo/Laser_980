
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"
								   
#define SPEED_LENGTH		3

__IOM uint16_t FlowSpeedVal[SPEED_LENGTH];

/* Configuration table -------------------------------------------------------*/
const BSP_GPIO_CONFIG s_stWaterLevelCfg[WATER_MAX_CHNL] = 
{
    /*******High Level***********/
    {
        .GpioPort    = WATER_H_PORT,
        .GpioPin     = WATER_H_PIN,
        .ActiveLogic = GPIO_PIN_RESET,
    },
	
	/*******Low Level***********/
    {
        .GpioPort    = WATER_L_PORT,
        .GpioPin     = WATER_L_PIN,
        .ActiveLogic = GPIO_PIN_RESET,
    },
};

static uint8_t BSP_ReadWaterLevelValue(uint8_t WaterLevelId);

void BSP_Water_Init(void)
{
	/* Water Flow */
	/* Close ADC DMA channel��Prevent repeated DMA interrupts */
	HAL_NVIC_DisableIRQ(BSP_WATERFLOW_DMA_CHNL_IRQn);
	/* Starts the TIM Input Capture measurement in DMA mode */
	HAL_TIM_IC_Start_DMA(BSP_SPEED_DETECTION_TIMX, BSP_WATERFLOW_DETECTION_CHNL, (uint32_t*)FlowSpeedVal, SPEED_LENGTH);

	/* Water Temperature */
}

void BSP_Water_DeInit(void)
{
}

/**
 * @brief  BSP_ReadWaterSpeed.
 * @note   None.
 * @param  None.
 * @retval FlowSpeed.
 */
uint16_t BSP_ReadWaterSpeed(void)
{
	uint16_t data[SPEED_LENGTH] = {0};
	uint16_t average = 0;
	uint8_t index;
	uint8_t location;
		
	location = SPEED_LENGTH - __HAL_DMA_GET_COUNTER(BSP_SPEED_DETECTION_TIMX->hdma[TIM_DMA_ID_CC1]);

	for (index = 0; index<SPEED_LENGTH; index++)
	{
		data[index] = FlowSpeedVal[(index + location) % SPEED_LENGTH];
	}
		
	for (index = 0; index < (SPEED_LENGTH -1); index++)
	{
		if (data[index + 1] < data[index])
		{
			data[index + 1] += 30000;	/* TIM ���� 30000 */
		}
		average += (data[index + 1] - data[index]);
	}
	average = average>>1;
		
	/*	SystemData.FanSpeed[0] = 72000000/720/avg */
	if (average >= 10)
	{
		average = (100000 / average);
	}
	else
	{
		average = 0;
	}
	
	for (index = 0; index < SPEED_LENGTH; index++)
	{
		FlowSpeedVal[index] = 0;
	}
	
	return average;
}

/**
 * @brief  BSP_ReadWaterSpeed.
 * @note   None.
 * @param  None.
 * @retval 0:ˮλ������1:ˮλƫ�ͣ�2:ȱˮ
 */
uint8_t BSP_ReadWaterLevel(void)
{
	uint8_t index;
    
    for (index = 0; index < WATER_MAX_CHNL; index++)
    {
        if (BSP_ReadWaterLevelValue(index) )
			break;
    }
	return index;
}

/**
 * @brief  BSP_ReadWaterLevelValue.
 * @note   None.
 * @param  WaterLevelId.
 * @retval 0xFF:ID Error.
 *		   0:
 *		   1:
 */
static uint8_t BSP_ReadWaterLevelValue(uint8_t WaterLevelId)
{
	GPIO_TypeDef	*GpioPort;
    uint32_t		GpioPin;
	GPIO_PinState 	ActiveLogic;
	
    if (WaterLevelId >= WATERFLOW_ID_MAX)
        return 0xFF;
	
	GpioPort = s_stWaterLevelCfg[WaterLevelId].GpioPort;
	GpioPin  = s_stWaterLevelCfg[WaterLevelId].GpioPin;
	ActiveLogic = s_stWaterLevelCfg[WaterLevelId].ActiveLogic;
	
    return (ActiveLogic == HAL_GPIO_ReadPin(GpioPort, GpioPin)); 
}
