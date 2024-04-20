#include "APP_Common.h"

__IOM Key_Struct s_stKeyTcb[KEY_ID_MAX];

static uint8_t Read_KeyState(uint8_t id);
extern void HCI_KeyProcCallback(uint8_t trigger);

static const KeyProcess Key_ProcessTbl[KEY_ID_MAX] = 
{
	HCI_KeyProcCallback,
	HCI_KeyProcCallback,
};

#if 0
/*****************************************************************************
Function name : APP_KEY_TimeProc
Description: APP Key 模块的时基函数，需要在定时器中定期调用。	 
Input: usPeriod->函数被调用的周期（ms）		
Return: NONE     
Notes:
******************************************************************************/
void APP_KEY_TimeProc(uint16_t usPeriod)
{
  static uint16_t AppKeyTB = 0;
  AppKeyTB += usPeriod;
  if (AppKeyTB >= TASK_HCI_KEY_TB)
  {
    Set_Task(HCI, HCI_KEY);
    AppKeyTB -= TASK_HCI_KEY_TB;
  }
}
#endif

/**
 * @brief		APP_KEY_Init.
 * @note		None.
 * @param		None;
 * @retval	None.
 */
void APP_KEY_Init(void)
{
  uint8_t index;

  memset((uint8_t *)&s_stKeyTcb, 0, sizeof(s_stKeyTcb));

  for (index = 0; index < KEY_ID_MAX; index++)
  {
    /*  s_stKeyTcb[index].id   = index; */
    s_stKeyTcb[index].process = Key_ProcessTbl[index];
    s_stKeyTcb[index].ucState = KEY_RELEASE;
    s_stKeyTcb[index].usLongTH = KEY_PUSH_10MSBASE350MS;
    s_stKeyTcb[index].ucTrigger = NO_PRO;
  }
}

/**
 * @brief		APP_KEY_Task.
 * @note		None.
 * @param		None;
 * @retval	None.
 */
void APP_KEY_Task(void)
{
  uint8_t index;

  uint16_t ucPeriod = APP_KEY_PERIOD;

  for (index = 0; index < KEY_ID_MAX; index++)
  {
#if 0
    if (KEY_PRESS == s_stKeyTcb[index].ucState)
    {
      if (KEY_PRESS == Read_KeyState(index))
      {
        if (s_stKeyTcb[index].usPressTime < s_stKeyTcb[index].usLongTH)
        {
          s_stKeyTcb[index].usPressTime += ucPeriod;

          if (s_stKeyTcb[index].usPressTime == s_stKeyTcb[index].usLongTH)
          {
            s_stKeyTcb[index].ucClickTimes = 0;
            /* long */
            s_stKeyTcb[index].process(LONG_PRO);
          }
        }
        else /* LONG_PRESSED_REPEAT */
        {
        }
      }
      else
      {
        if ((s_stKeyTcb[index].usPressTime > KEY_PUSH_10MSBASE50MS) && (s_stKeyTcb[index].usPressTime < s_stKeyTcb[index].usLongTH))
        {
          s_stKeyTcb[index].ucClickTimes++;
          if (2 == s_stKeyTcb[index].ucClickTimes)
          {
            s_stKeyTcb[index].ucClickTimes = 0;
            /* double-click */
            s_stKeyTcb[index].process(DOUBLE_PRO);
          }
        }
        s_stKeyTcb[index].usReleaseTine = 0;
        s_stKeyTcb[index].usPressTime = 0;
        s_stKeyTcb[index].ucState = KEY_RELEASE;
      }
    }
    else
    {
      if (KEY_PRESS == Read_KeyState(index))
      {
        s_stKeyTcb[index].usPressTime += ucPeriod;
        s_stKeyTcb[index].ucState = KEY_PRESS;
      }
      else
      {
        if (s_stKeyTcb[index].usReleaseTine <= KEY_PUSH_10MSBASE1S)
        {
          s_stKeyTcb[index].usReleaseTine += ucPeriod;
        }
        if ((1 == s_stKeyTcb[index].ucClickTimes) && (s_stKeyTcb[index].usReleaseTine > KEY_PUSH_10MSBASE1S))
        {
          s_stKeyTcb[index].ucClickTimes = 0;
          s_stKeyTcb[index].usReleaseTine = 0;
          /* short */
          s_stKeyTcb[index].process(SHOURT_PRO);
        }
        s_stKeyTcb[index].usPressTime = 0;
        s_stKeyTcb[index].ucState = KEY_RELEASE;
      }
    }
#else
    if (KEY_PRESS == s_stKeyTcb[index].ucState)
    {
      if (KEY_PRESS == Read_KeyState(index))
      {
        if (s_stKeyTcb[index].usPressTime < s_stKeyTcb[index].usLongTH)
        {
          s_stKeyTcb[index].usPressTime += ucPeriod;
          if (s_stKeyTcb[index].usPressTime == s_stKeyTcb[index].usLongTH)
          {
            /* Long */
            s_stKeyTcb[index].ucTrigger = LONG_PRO;
          }
        }
      }
      else
      {
        s_stKeyTcb[index].ucState = KEY_RELEASE;
        s_stKeyTcb[index].usReleaseTine = 0;
      }
    }
    else
    {
      if (KEY_PRESS == Read_KeyState(index))
      {
        s_stKeyTcb[index].usPressTime += ucPeriod;
        s_stKeyTcb[index].ucState = KEY_PRESS;
      }
      else
      {
        if (s_stKeyTcb[index].usReleaseTine < KEY_PUSH_10MSBASE100MS)
        {
          s_stKeyTcb[index].usReleaseTine += ucPeriod;
          if (s_stKeyTcb[index].usReleaseTine == KEY_PUSH_10MSBASE100MS)
          {
            s_stKeyTcb[index].ucTrigger = NO_PRO;
            s_stKeyTcb[index].usPressTime = 0;
          }
        }
        s_stKeyTcb[index].ucState = KEY_RELEASE;
      }
    }
#endif
  }
}

/**
 * @brief		Read_KeyState.
 * @note		None.
 * @param		id:key index;
 * @retval	State.
 */
static uint8_t Read_KeyState(uint8_t id)
{
  if (id >= KEY_ID_MAX)
    return KEY_ERROR;

  return ((BSP_ReadKeyValue(id) == 1) ? KEY_PRESS : KEY_RELEASE);
}

/**
 * @brief		APP_SetKeyDelay.
 * @note		None.
 * @param		id:key index;
 *		  		bState:true,false;
 * @retval	HandpieceState.
 */
void APP_KEY_DelayConfig(uint8_t id, bool bState)
{
  if (id >= KEY_ID_MAX)
    return;

  if (bState)
    s_stKeyTcb[id].usLongTH = KEY_PUSH_10MSBASE350MS;
  else
    s_stKeyTcb[id].usLongTH = KEY_PUSH_10MSBASE100MS;
}

/**
 * @brief  APP_KeyReturnVal.
 * @note   None.
 * @param  id:key index;
 * @retval .
 */
uint8_t APP_Key_ReadVal(uint8_t id)
{
  if (id >= KEY_ID_MAX)
    return 0xFF;

  return s_stKeyTcb[id].ucTrigger;
}

/**
 * @brief  APP_KEY_IsPress.
 * @note   None.
 * @param  None;
 * @retval bool.
 */
bool APP_KEY_IsPress(void)
{
  for (uint8_t index = 0; index < KEY_ID_MAX; index++)
  {
    if (APP_Key_ReadVal(index) == LONG_PRO)
      return true;
  }
  return false;
}
