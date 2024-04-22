#ifndef __BSP_Common_H__
#define __BSP_Common_H__

#ifdef __cplusplus
 extern "C" {
#endif
 
#include "global.h"

#include "main.h"
#include "dma.h"
#include "tim.h"
#include "adc.h"
//#include "dac.h"
#include "usart.h"

#include "GoldDebug.h"

#include "Configure.h"

#include "Stm32Flash/flash_stm32.h"

#include "iap/inc/iap.h"

#include "BSP/BSP_GPIO.h"
//#include "BSP/BSP_Handpiece.h"
//#include "BSP/BSP_Pump.h"
//#include "BSP/BSP_Key.h"
//#include "BSP/BSP_Water.h"
#include "BSP/BSP_Adc.h"
//#include "BSP/BSP_Cooler.h"
//#include "BSP/BSP_Frequency.h"
//#include "BSP/BSP_Power.h"
#include "BSP/BSP_Uart.h"
//#include "BSP/BSP_SafeLocker.h"
#include "BSP/BSP_LED.h"
#include "BSP/BSP_Motor.h"
#include "BSP/BSP_Laser.h"

//#include "MAX5400/MAX5400.h"
//#include "AD840X/AD840X.h"
 
#define NO_APP			
#define DOWN_TO_FAC							0xA0
#define DOWN_TO_DWN							0XAA
#define COPY_TO_DWN							0X55
#define COPY_TO_APP							0X5A
#define ENTER_APP								0XA5
#define UPLOAD_APP_PRO					0x50
#define UPLOAD_APP_HANDPIECE_0	0x60
#define UPLOAD_APP_HANDPIECE_1	0x70
#define UPLOAD_APP_FAN					0x80

//#define TICK_INT_PRIORITY_DEF             (3U)    /*!< tick interrupt priority */  
//#define TIM2_INT_PRIORITY_DEF             (1U)    

#define __BSP_TIM_ENABLE_CCIT(__HANDLE__, __CHANNEL__)  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->DIER |= (TIM_IT_CC1)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->DIER |= (TIM_IT_CC2)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->DIER |= (TIM_IT_CC3)) :\
   ((__HANDLE__)->Instance->DIER |= (TIM_IT_CC4)))
   
#define __BSP_TIM_DISABLE_CCIT(__HANDLE__, __CHANNEL__)  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->DIER &= ~(TIM_IT_CC1)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->DIER &= ~(TIM_IT_CC2)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->DIER &= ~(TIM_IT_CC3)) :\
   ((__HANDLE__)->Instance->DIER &= ~(TIM_IT_CC4)))

#define DEV_MAIN_PORT (&huart1)

typedef enum
{
  EXE_OK = 0x00U,
  EXE_ERROR = 0x01U,
  EXE_BUSY = 0x02U,
  EXE_TIMEOUT = 0x03U,
} Execute_StatusTypeDef;

void BSP_Init(void);

#endif
