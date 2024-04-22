
#ifndef __BSP_GPIO_H__
#define __BSP_GPIO_H__

/**
 * @brief  MCU GPIO pin working mode for GPIO
 */
typedef enum
{
  GPIO_MODE_IN = 0x00, /*!< Work as GPIO input */
  GPIO_MODE_EXTI,      /*!< Work as EXTI */
  GPIO_MODE_OUT,       /*!< Work as GPIO output */

} GpioMode;

typedef struct
{
  GPIO_TypeDef *GpioPort;
  uint32_t GpioPin;
  GPIO_PinState ActiveLogic;
} BSP_GPIO_CONFIG;

//=============================== Function definition ===============================//
#define BSP_GPIO_RESET(x)			HAL_GPIO_WritePin(x##_PORT, x##_PIN, GPIO_PIN_RESET)
#define BSP_GPIO_SET(x)		    HAL_GPIO_WritePin(x##_PORT, x##_PIN, GPIO_PIN_SET)
#define BSP_GPIO_TOGGLE(x)    HAL_GPIO_TogglePin(x##_PORT, x##_PIN)
#define BSP_GPIO_READ(x)			HAL_GPIO_ReadPin(x##_PORT, x##_PIN)

#define BSP_Digital_Write			HAL_GPIO_WritePin
#define BSP_Digital_Read			HAL_GPIO_ReadPin

#endif
