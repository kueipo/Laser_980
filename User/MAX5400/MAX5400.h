/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAX5400_H
#define __MAX5400_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/***********************   Max5400 GPIO Definition  ***************************/
/* CS */
#define Max5400_CS_GPIO_CLK_ENABLE() \
																__HAL_RCC_GPIOD_CLK_ENABLE()
#define Max5400_CS_PORT					GPIOD
#define Max5400_CS_PIN					GPIO_PIN_2

/* SDA */
#define Max5400_SDA_GPIO_CLK_ENABLE() \
																__HAL_RCC_GPIOB_CLK_ENABLE()
#define Max5400_SDA_PORT       	GPIOB
#define Max5400_SDA_PIN        	GPIO_PIN_3

/* SCLK */
#define Max5400_SCLK_GPIO_CLK_ENABLE() \
																__HAL_RCC_GPIOB_CLK_ENABLE()
#define Max5400_SCLK_PORT				GPIOB
#define Max5400_SCLK_PIN				GPIO_PIN_4

/*********************   Max5400 Function Definition  *************************/
#define Max5400_CS_LOW()				HAL_GPIO_WritePin(Max5400_CS_PORT, Max5400_CS_PIN, GPIO_PIN_RESET) 
#define Max5400_CS_HIGH()				HAL_GPIO_WritePin(Max5400_CS_PORT, Max5400_CS_PIN, GPIO_PIN_SET)

#define Max5400_SDA_LOW()       HAL_GPIO_WritePin(Max5400_SDA_PORT, Max5400_SDA_PIN, GPIO_PIN_RESET) 
#define Max5400_SDA_HIGH()      HAL_GPIO_WritePin(Max5400_SDA_PORT, Max5400_SDA_PIN, GPIO_PIN_SET)

#define Max5400_SCLK_LOW()			HAL_GPIO_WritePin(Max5400_SCLK_PORT, Max5400_SCLK_PIN, GPIO_PIN_RESET) 
#define Max5400_SCLK_HIGH()			HAL_GPIO_WritePin(Max5400_SCLK_PORT, Max5400_SCLK_PIN, GPIO_PIN_SET)

/* External functions --------------------------------------------------------*/
void Max5400_Init(void);
void Max5400_WriteByte(uint8_t data);

#endif /* __MAX5400_H */
