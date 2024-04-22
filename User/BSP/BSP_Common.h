#ifndef __BSP_Common_H__
#define __BSP_Common_H__
  
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "adc.h"
#include "dac.h"
#include "usart.h"

#include "global.h"
#include "Configure.h"
#include <easyflash.h>
#include "fal.h"
#include "sys/ConfigFlag.h"

//#include "MAX5400/MAX5400.h"
//#include "AD840X/AD840X.h"
#include "Sys/Filter.h"

#include "BSP/BSP_GPIO.h"
#include "BSP/BSP_Handpiece.h"
//#include "BSP/BSP_Pump.h"
#include "BSP/BSP_Key.h"
//#include "BSP/BSP_Water.h"
#include "BSP/BSP_Adc.h"
#include "BSP/BSP_Cooler.h"
#include "BSP/BSP_Frequency.h"
#include "BSP/BSP_DAC.h"
#include "BSP/BSP_Uart.h"
#include "BSP/BSP_SafeLocker.h"
#include "BSP/BSP_LED.h"
#include "BSP/BSP_FAN.h"
#include "BSP/BSP_Buzzer.h"

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

#define __BSP_TIM_CLEAR_CCIT_FLAG(__HANDLE__, __CHANNEL__)  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->SR &= ~(TIM_FLAG_CC1)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->SR &= ~(TIM_FLAG_CC2)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->SR &= ~(TIM_FLAG_CC3)) :\
   ((__HANDLE__)->Instance->SR &= ~(TIM_FLAG_CC4)))

#define __BSP_TIM_TRIGGER_ENABLE(__HANDLE__) \
	(__HANDLE__)->Instance->SMCR |= TIM_SLAVEMODE_TRIGGER;
	
#define __BSP_TIM_TRIGGER_DISABLE(__HANDLE__) \
	(__HANDLE__)->Instance->SMCR &= ~TIM_SMCR_SMS;


#define __BSP_TIM_OPM_ENABLE(__HANDLE__) \
	(__HANDLE__)->Instance->CR1 |= TIM_OPMODE_SINGLE;
  
#define __BSP_TIM_OPM_DISABLE(__HANDLE__) \
  (__HANDLE__)->Instance->CR1 &= ~TIM_CR1_OPM;


void BSP_Init(void);

#endif
