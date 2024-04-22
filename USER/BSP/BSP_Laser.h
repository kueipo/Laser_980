
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_POWER_H__
#define __BSP_POWER_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
typedef struct
{
	uint32_t MaxVal;
	TIM_HandleTypeDef *htim;
	BSP_GPIO_CONFIG power;
} BSP_LASER_CONFIG;

/************* LD_POWER ****************/	   
#define LD_POWER_PORT     LD_POWER_GPIO_Port
#define LD_POWER_PIN      LD_POWER_Pin
#define LD_POWER_LOGIC    GPIO_PIN_SET

#define LD_TIM						(&htim14)

#define LD_ADC_CHNL				ADC_CHANNEL_6

/* External functions --------------------------------------------------------*/
void BSP_Laser_Init(void);	 
void BSP_Laser_DeInit(void);
void BSP_Laser_Enable(bool bstate);

void BSP_Laser_TimEnable(bool bstate);
void BSP_Laser_TimSet(uint16_t period);
void BSP_Laser_AdcWDGSet(uint16_t high, uint16_t low);

#endif
