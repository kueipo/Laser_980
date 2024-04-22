
#ifndef __APP_H
#define __APP_H

#include "DEV_Config.h"



HAL_StatusTypeDef TIM_PWM_Init(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t Channel2);
HAL_StatusTypeDef TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t Channel2);
HAL_StatusTypeDef TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t Channel2);

#endif
