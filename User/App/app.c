
#include "APP/APP_Common.h"

HAL_StatusTypeDef TIM_PWM_Init(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t Channel2)
{
  /* Check the parameters */
  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  /* Check the TIM channel state */
  if (TIM_CHANNEL_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
  {
    return HAL_ERROR;
  }

  /* Set the TIM channel state */
  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);

  /* Enable the Capture compare channel */
  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE);
  TIM_CCxChannelCmd(htim->Instance, Channel2, TIM_CCx_ENABLE);

  __HAL_TIM_ENABLE_IT(htim, TIM_IT_UPDATE);

  /* Return function status */
  return HAL_OK;
}

HAL_StatusTypeDef TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t Channel2)
{
  /* Check the parameters */
  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {
    /* Disable the Main Output */
    /* __HAL_TIM_MOE_DISABLE(htim); */
    (htim)->Instance->BDTR &= ~(TIM_BDTR_MOE);
  }

  (htim)->Instance->CR1 &= ~(TIM_CR1_CEN);

  /* Set the TIM channel state */
  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_READY);

  /* Return function status */
  return HAL_OK;
}

HAL_StatusTypeDef TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t Channel2)
{
  uint32_t tmpsmcr;

  /* Check the parameters */
  assert_param(IS_TIM_CCX_INSTANCE(htim->Instance, Channel));

  /* Check the TIM channel state */
  if (TIM_CHANNEL_STATE_GET(htim, Channel) != HAL_TIM_CHANNEL_STATE_READY)
  {
    return HAL_ERROR;
  }

  /* Set the TIM channel state */
  TIM_CHANNEL_STATE_SET(htim, Channel, HAL_TIM_CHANNEL_STATE_BUSY);

  /* Enable the Capture compare channel */
  /*  TIM_CCxChannelCmd(htim->Instance, Channel, TIM_CCx_ENABLE); */
  /*	TIM_CCxChannelCmd(htim->Instance, Channel2, TIM_CCx_ENABLE); */

  if (IS_TIM_BREAK_INSTANCE(htim->Instance) != RESET)
  {
    /* Enable the main output */
    __HAL_TIM_MOE_ENABLE(htim);
  }

  /* Enable the Peripheral, except in trigger mode where enable is automatically done with trigger */
  if (IS_TIM_SLAVE_INSTANCE(htim->Instance))
  {
    tmpsmcr = htim->Instance->SMCR & TIM_SMCR_SMS;
    if (!IS_TIM_SLAVEMODE_TRIGGER_ENABLED(tmpsmcr))
    {
      /*  __HAL_TIM_ENABLE(htim); */
      (htim)->Instance->CR1 |= (TIM_CR1_CEN);
    }
  }
  else
  {
    /*  __HAL_TIM_ENABLE(htim); */
    (htim)->Instance->CR1 |= (TIM_CR1_CEN);
  }

  /* Return function status */
  return HAL_OK;
}
