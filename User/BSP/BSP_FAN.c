
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"
								   
/* Configuration table -------------------------------------------------------*/
const BSP_FAN_CONFIG s_stFanBspCfg[FAN_ID_MAX] = 
{
	/******* FAN_ID_0 ***********/
  {
		.htim = &htim1,
		.Channel = TIM_CHANNEL_3,
		.inputhtim = &htim2,
		.inputChannel = TIM_CHANNEL_3,
  },
	/******* FAN_ID_1 ***********/
  {
		.htim = &htim1,
		.Channel = TIM_CHANNEL_3,
		.inputhtim = &htim2,
		.inputChannel = TIM_CHANNEL_4,
  },
};

typedef struct 
{
	volatile uint16_t pulse;
	volatile uint16_t speed[FAN_ID_MAX];
	volatile uint8_t overtime;
	volatile uint8_t period;
	volatile uint8_t step;
	volatile uint8_t CompleteFlg;
	volatile uint8_t id;
	volatile bool RunFlg;
}Fan_Struct;
Fan_Struct s_stFanBspTcb;

/* Private macro -------------------------------------------------------------*/
#define __BSP_TIM_ENABLE_CHNL(__HANDLE__, __CHANNEL__)  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->DIER |= (TIM_IT_CC1)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->DIER |= (TIM_IT_CC2)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->DIER |= (TIM_IT_CC3)) :\
   ((__HANDLE__)->Instance->DIER |= (TIM_IT_CC4)))

#define __BSP_TIM_DISABLE_CHNL(__HANDLE__, __CHANNEL__)  \
  (((__CHANNEL__) == TIM_CHANNEL_1) ? ((__HANDLE__)->Instance->DIER &= ~(TIM_IT_CC1)) :\
   ((__CHANNEL__) == TIM_CHANNEL_2) ? ((__HANDLE__)->Instance->DIER &= ~(TIM_IT_CC2)) :\
   ((__CHANNEL__) == TIM_CHANNEL_3) ? ((__HANDLE__)->Instance->DIER &= ~(TIM_IT_CC3)) :\
   ((__HANDLE__)->Instance->DIER &= ~(TIM_IT_CC4)))

static void BSP_Fan_CaptureStart(uint8_t id);
static void BSP_Fan_CaptureStop(uint8_t id);

/**
 * @brief  BSP_Fan_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Fan_Init(void)
{
	for (uint8_t index = 0; index < FAN_ID_MAX; index++)
	{
		BSP_Fan_Config(index, 0);
		BSP_Fan_Operate(index, FAN_ON);
	}
}

/**
 * @brief  BSP_Fan_DeInit.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Fan_DeInit(void)
{
}

/**
 * @brief  BSP_Fan_Task.
 * @note   None.
 * @param  htim.
 * @retval None.
 */
void BSP_Fan_Task(void)
{
	if (s_stFanBspTcb.CompleteFlg)
	{
		// over time
		if (s_stFanBspTcb.CompleteFlg > 1)
			s_stFanBspTcb.speed[s_stFanBspTcb.id] = 0;
		else // success
		{		
			uint32_t temp;
			temp = 100000 / (s_stFanBspTcb.pulse + 10000 * s_stFanBspTcb.period);
			s_stFanBspTcb.speed[s_stFanBspTcb.id] = (uint16_t)temp;
		}
		
		s_stFanBspTcb.CompleteFlg = 0;
		
		++s_stFanBspTcb.id;
		s_stFanBspTcb.id %= FAN_ID_MAX;
	}
	
	BSP_Fan_CaptureStart(s_stFanBspTcb.id);
}

/**
 * @brief  BSP_Fan_Operate.
 * @note   None.
 * @param  id;
 *		   	 FanOpMode:
 *					FAN_HOLD:
 *					FAN_ON:
 *					FAM_OFF:
 * @retval None.
 */
void BSP_Fan_Operate(uint8_t id, uint8_t FanOpMode)
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;

	if (id >= FAN_ID_MAX)
		return;

	htim = s_stFanBspCfg[id].htim;
	Channel = s_stFanBspCfg[id].Channel;

	switch (FanOpMode)
	{
	case FAN_OFF:
		/* Check the TIM complementary channel state */
#if 1
		if (TIM_CHANNEL_N_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
			HAL_TIMEx_PWMN_Stop(htim, Channel);
#else
		if (TIM_CHANNEL_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
			HAL_TIM_PWM_Stop(htim, Channel);
#endif
		break;

	case FAN_ON:
		/* Check the TIM complementary channel state */
#if 1
		HAL_TIMEx_PWMN_Start(htim, Channel);
#else
		HAL_TIM_PWM_Start(htim, Channel);
#endif
		break;

	case FAN_HOLD:
		break;

	default:
		break;
	}
}

/**
 * @brief  BSP_Fan_Config.
 * @note   None.
 * @param  id, uiPwmOut:0-100.
 * @retval None.
 */
void BSP_Fan_Config(uint8_t id, uint16_t uiPwmOut)
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;

	if (id >= FAN_ID_MAX)
		return;

	htim = s_stFanBspCfg[id].htim;
	Channel = s_stFanBspCfg[id].Channel;
	
	/* Set duty cycle */
	__HAL_TIM_SET_COMPARE(htim, Channel, uiPwmOut);
	/* Set period  */
	/*	__HAL_TIM_SET_AUTORELOAD(htim, Period); */
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
/**
 * @brief  BSP_Fan_CaptureStart.
 * @note   None.
 * @param  id.
 * @retval None.
 */
static void BSP_Fan_CaptureStart(uint8_t id)
{
	if (s_stFanBspTcb.RunFlg)
		return;
	
	TIM_HandleTypeDef *htim = s_stFanBspCfg[id].inputhtim;
	uint32_t Channel = s_stFanBspCfg[id].inputChannel;
	
	__HAL_TIM_SetCounter(htim, 0);
	__HAL_TIM_CLEAR_FLAG(htim, TIM_FLAG_UPDATE);
	
#if 0
	HAL_TIM_IC_Start_IT(htim, Channel);
	HAL_TIM_Base_Start_IT(htim);
#else
	__BSP_TIM_ENABLE_CHNL(htim, Channel);
	TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);
	
	__HAL_TIM_ENABLE_IT(htim, TIM_IT_UPDATE);
	__HAL_TIM_ENABLE(htim);
#endif
	
	s_stFanBspTcb.period = 0;
	s_stFanBspTcb.overtime = 0;
	s_stFanBspTcb.RunFlg = true;
	s_stFanBspTcb.step = 0;
}

/**
 * @brief  BSP_Fan_CaptureStop.
 * @note   None.
 * @param  id.
 * @retval None.
 */
static void BSP_Fan_CaptureStop(uint8_t id)
{
	TIM_HandleTypeDef *htim = s_stFanBspCfg[id].inputhtim;
	uint32_t Channel = s_stFanBspCfg[id].inputChannel;

#if 0
	HAL_TIM_IC_Stop_IT(htim, Channel);
	HAL_TIM_Base_Stop_IT(htim);
#else
	__BSP_TIM_DISABLE_CHNL(htim, Channel);
	TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_DISABLE);
	
	__HAL_TIM_DISABLE_IT(htim, TIM_IT_UPDATE);
	__HAL_TIM_DISABLE(htim);
#endif
	
	s_stFanBspTcb.RunFlg = false;
}

/**
 * @brief  BSP_Fan_CaptureStop.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Fan_CaptureOverflow(void)
{
	uint8_t id = s_stFanBspTcb.id;
	if (s_stFanBspTcb.step == 1)
	{
		if (s_stFanBspTcb.period == 10)
		{
			BSP_Fan_CaptureStop(id);
			s_stFanBspTcb.CompleteFlg = 2;
		}
		else
			s_stFanBspTcb.period++;
	}
	else
	{
		if (++s_stFanBspTcb.overtime > 10)
		{
			BSP_Fan_CaptureStop(id);
			s_stFanBspTcb.CompleteFlg = 2;
		}
	}
}

/**
 * @brief  BSP_Fan_Capture.
 * @note   None.
 * @param  htim.
 * @retval None.
 */
void BSP_Fan_Capture(TIM_HandleTypeDef *htim)
{
	uint8_t index;
	
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3)
		index = FAN_ID_0;
	else if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4)
		index = FAN_ID_1;
	else
		return;
	
	if (s_stFanBspTcb.step == 0) //
	{
		__HAL_TIM_SetCounter(htim, 0);
		s_stFanBspTcb.step = 1;
	}
	else
	{
		s_stFanBspTcb.pulse = HAL_TIM_ReadCapturedValue(htim, s_stFanBspCfg[index].inputChannel);
		BSP_Fan_CaptureStop(index);
		s_stFanBspTcb.CompleteFlg = 1;
	}
}
