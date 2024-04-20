/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __AD840X_H
#define __AD840X_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/***********************   AD840X GPIO Definition   ***************************/
/* CS */
#define AD840X_CS_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOD_CLK_ENABLE()
#define AD840X_CS_PORT								GPIOD
#define AD840X_CS_PIN									GPIO_PIN_2

/* SDA */
#define AD840X_SDA_GPIO_CLK_ENABLE()	__HAL_RCC_GPIOB_CLK_ENABLE()
#define AD840X_SDA_PORT               GPIOB
#define AD840X_SDA_PIN                GPIO_PIN_3

/* SCLK */
#define AD840X_SCLK_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define AD840X_SCLK_PORT              GPIOB
#define AD840X_SCLK_PIN               GPIO_PIN_4

/*********************   AD840X Function Definition  *************************/
#define AD840X_CS_LOW()               HAL_GPIO_WritePin(AD840X_CS_PORT, AD840X_CS_PIN, GPIO_PIN_RESET) 
#define AD840X_CS_HIGH()              HAL_GPIO_WritePin(AD840X_CS_PORT, AD840X_CS_PIN, GPIO_PIN_SET)

#define AD840X_SDA_LOW()              HAL_GPIO_WritePin(AD840X_SDA_PORT, AD840X_SDA_PIN, GPIO_PIN_RESET) 
#define AD840X_SDA_HIGH()             HAL_GPIO_WritePin(AD840X_SDA_PORT, AD840X_SDA_PIN, GPIO_PIN_SET)

#define AD840X_SCLK_LOW()							HAL_GPIO_WritePin(AD840X_SCLK_PORT, AD840X_SCLK_PIN, GPIO_PIN_RESET) 
#define AD840X_SCLK_HIGH()						HAL_GPIO_WritePin(AD840X_SCLK_PORT, AD840X_SCLK_PIN, GPIO_PIN_SET)

/* External functions --------------------------------------------------------*/
void AD840X_Init(void);
void AD840X_WriteByte(uint8_t addr, uint8_t data);

#endif /* __AD840X_H */
