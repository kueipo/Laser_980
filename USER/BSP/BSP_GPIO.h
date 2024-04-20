#ifndef   __BSP_GPIO_H__
#define   __BSP_GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif
     
/**
 * @brief  MCU GPIO pin working mode for GPIO
 */
typedef enum
{
  GPIO_MODE_IN  = 0x00,     /*!< Work as GPIO input */
  GPIO_MODE_EXTI,           /*!< Work as EXTI */
  GPIO_MODE_OUT,            /*!< Work as GPIO output */
}GpioMode;

typedef struct
{
  GPIO_TypeDef *GpioPort;   
  uint32_t GpioPin; 
  GPIO_PinState ActiveLogic;
}BSP_GPIO_CONFIG;

/* POWER ON */
#define GPRS_POWER_ON_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOE_CLK_ENABLE()
#define GPRS_POWER_ON_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOE_CLK_DISABLE()
#define GPRS_POWER_ON_PORT                      GPIOE
#define GPRS_POWER_ON_PIN                       GPIO_PIN_13

/* WAKE UP */
#define GPRS_WAKE_UP_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOE_CLK_ENABLE()
#define GPRS_WAKE_UP_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOE_CLK_DISABLE()
#define GPRS_WAKE_UP_PORT                      GPIOE
#define GPRS_WAKE_UP_PIN                       GPIO_PIN_14

/* DCDC EN */
#define GPRS_DCDC_EN_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define GPRS_DCDC_EN_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()
#define GPRS_DCDC_EN_PORT                      GPIOB
#define GPRS_DCDC_EN_PIN                       GPIO_PIN_12

/* BEEP */
#define BEEP_GPIO_CLK_ENABLE()                 __HAL_RCC_GPIOE_CLK_ENABLE()
#define BEEP_GPIO_CLK_DISABLE()                __HAL_RCC_GPIOE_CLK_DISABLE()
#define BEEP_PORT                              GPIOE
#define BEEP_PIN                               GPIO_PIN_3
    
/* NTC Power CTRL */
#define NTC_POWER_CTRL_GPIO_CLK_ENABLE()       __HAL_RCC_GPIOE_CLK_ENABLE()
#define NTC_POWER_CTRL_GPIO_CLK_DISABLE()      __HAL_RCC_GPIOE_CLK_DISABLE()
#define NTC_POWER_CTRL_PORT                    GPIOE
#define NTC_POWER_CTRL_PIN                     GPIO_PIN_2
 
/* TP */
#define TP_GPIO_CLK_ENABLE()                   __HAL_RCC_GPIOD_CLK_ENABLE()
#define TP_GPIO_CLK_DISABLE()                  __HAL_RCC_GPIOD_CLK_DISABLE()
#define TP_PORT                                GPIOD
#define TP_PIN                                 GPIO_PIN_8
//=============================== Function definition ===============================//                                        
#define BSP_GPIO_RESET(x)			HAL_GPIO_WritePin(x##_PORT, x##_PIN, GPIO_PIN_RESET)
#define BSP_GPIO_SET(x)		    HAL_GPIO_WritePin(x##_PORT, x##_PIN, GPIO_PIN_SET)
#define BSP_GPIO_TOGGLE(x)    HAL_GPIO_TogglePin(x##_PORT, x##_PIN)
#define BSP_GPIO_READ(x)			HAL_GPIO_ReadPin(x##_PORT, x##_PIN)

#define BSP_Digital_Write			HAL_GPIO_WritePin
#define BSP_Digital_Read			HAL_GPIO_ReadPin

#define BSP_BEEP_ON()         BSP_GPIO_SET(BEEP)
#define BSP_BEEP_OFF()        BSP_GPIO_RESET(BEEP)
#define BSP_BEEP_TOGGLE()     BSP_GPIO_TOGGLE(BEEP)

#define BSP_DCDC_ENABLE()     BSP_GPIO_SET(GPRS_DCDC_EN)
#define BSP_DCDC_DISABLE()    BSP_GPIO_RESET(GPRS_DCDC_EN)

#ifdef __cplusplus
}
#endif 

#endif
