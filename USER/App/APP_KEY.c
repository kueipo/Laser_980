#include "APP_Common.h"

__IOM Key_Struct s_stKeyTcb[KEY_ID_MAX];

static uint8_t Read_KeyState(uint8_t KeyId);
extern void HCI_KeyProcCallback(uint8_t trigger);

static const KeyProcess Key_ProcessTbl[KEY_ID_MAX] = 
{
  HCI_KeyProcCallback,
	HCI_KeyProcCallback,
};

/*****************************************************************************
Function name : APP_KEY_TimeProc
Description: APP Key 模块的时基函数，需要在定时器中定期调用。	 
Input: usPeriod->函数被调用的周期（ms）		
Return: NONE     
Notes:
******************************************************************************/
#if 0
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

/*****************************************************************************
Function name : APP_KEY_Init
Description: APP Key 模块的初始化函数，在程序上电初始化的时候调用。
Input: NONE
Return: NONE
Notes:
******************************************************************************/
void APP_KEY_Init(void)
{
	uint8_t ucIndex;

	memset((uint8_t *)&s_stKeyTcb, 0, sizeof(s_stKeyTcb));

	for (ucIndex = 0; ucIndex < KEY_ID_MAX; ucIndex++)
	{
		/*  s_stKeyTcb[ucIndex].KeyId   = ucIndex; */
		s_stKeyTcb[ucIndex].process = Key_ProcessTbl[ucIndex];
		s_stKeyTcb[ucIndex].ucState = KEY_RELEASE;
		s_stKeyTcb[ucIndex].usLongTH = KEY_PUSH_10MSBASE350MS;
		s_stKeyTcb[ucIndex].ucTrigger = NO_PRO;
	}
}

/*****************************************************************************
Function name : APP_KEY_Task
Description: APP Key模块的任务，在HCI_Task中当HCI_KEY事件被置位的时候，将被执行。
Input: NONE
Return: NONE
Notes:
******************************************************************************/
void APP_KEY_Task(void)
{
	uint8_t ucIndex;

	/*运行周期*/
	uint16_t ucPeriod = APP_KEY_PERIOD;

	for (ucIndex = 0; ucIndex < KEY_ID_MAX; ucIndex++)
	{
#if 0
		if (KEY_PUSH == s_stKeyTcb[ucIndex].ucState)
		{
			if (KEY_PUSH == Read_KeyState(ucIndex))
			{
				if (s_stKeyTcb[ucIndex].usTime < s_stKeyTcb[ucIndex].usLongTH)
				{
					s_stKeyTcb[ucIndex].usTime += ucPeriod;

					if (s_stKeyTcb[ucIndex].usTime == s_stKeyTcb[ucIndex].usLongTH)
					{
						s_stKeyTcb[ucIndex].ucKeyDtcNum = 0;
						/* 长按处理 */
						s_stKeyTcb[ucIndex].process(LONG_PRO);
					}
				}
				else /* 连按处理 */
				{
				}
			}
			else
			{
				if ((s_stKeyTcb[ucIndex].usTime > KEY_PUSH_10MSBASE50MS) && (s_stKeyTcb[ucIndex].usTime < s_stKeyTcb[ucIndex].usLongTH))
				{
					s_stKeyTcb[ucIndex].ucKeyDtcNum++;
					if (2 == s_stKeyTcb[ucIndex].ucKeyDtcNum)
					{
						s_stKeyTcb[ucIndex].ucKeyDtcNum = 0;
						/* 双击处理 */
						s_stKeyTcb[ucIndex].process(DOUBLE_PRO);
					}
				}
				s_stKeyTcb[ucIndex].usTS = 0;
				s_stKeyTcb[ucIndex].usTime = 0;
				s_stKeyTcb[ucIndex].ucState = KEY_RELEASE;
			}
		}
		else
		{
			if (KEY_PUSH == Read_KeyState(ucIndex))
			{
				s_stKeyTcb[ucIndex].usTime += ucPeriod;
				s_stKeyTcb[ucIndex].ucState = KEY_PUSH;
			}
			else
			{
				if (s_stKeyTcb[ucIndex].usTS <= KEY_PUSH_10MSBASE1S)
				{
					s_stKeyTcb[ucIndex].usTS += ucPeriod;
				}
				if ((1 == s_stKeyTcb[ucIndex].ucKeyDtcNum) && (s_stKeyTcb[ucIndex].usTS > KEY_PUSH_10MSBASE1S))
				{
					s_stKeyTcb[ucIndex].ucKeyDtcNum = 0;
					s_stKeyTcb[ucIndex].usTS = 0;
					/* 短按处理 */
					s_stKeyTcb[ucIndex].process(SHOURT_PRO);
				}
				s_stKeyTcb[ucIndex].usTime = 0;
				s_stKeyTcb[ucIndex].ucState = KEY_RELEASE;
			}
		}
#else
		if (KEY_PUSH == s_stKeyTcb[ucIndex].ucState)
		{
			if (KEY_PUSH == Read_KeyState(ucIndex))
			{
				if (s_stKeyTcb[ucIndex].usTime < s_stKeyTcb[ucIndex].usLongTH)
				{
					s_stKeyTcb[ucIndex].usTime += ucPeriod;
					if (s_stKeyTcb[ucIndex].usTime == s_stKeyTcb[ucIndex].usLongTH)
					{
						/* 长按处理 */
						s_stKeyTcb[ucIndex].ucTrigger = LONG_PRO;
					}
				}
			}
			else
			{
				s_stKeyTcb[ucIndex].ucState = KEY_RELEASE;
				s_stKeyTcb[ucIndex].usTS = 0;
			}
		}
		else
		{
			if (KEY_PUSH == Read_KeyState(ucIndex))
			{
				s_stKeyTcb[ucIndex].usTime += ucPeriod;
				s_stKeyTcb[ucIndex].ucState = KEY_PUSH;
			}
			else
			{
				if (s_stKeyTcb[ucIndex].usTS < KEY_PUSH_10MSBASE100MS)
				{
					s_stKeyTcb[ucIndex].usTS += ucPeriod;
					if (s_stKeyTcb[ucIndex].usTS == KEY_PUSH_10MSBASE100MS)
					{
						s_stKeyTcb[ucIndex].ucTrigger = NO_PRO;
						s_stKeyTcb[ucIndex].usTime = 0;
					}
				}
				s_stKeyTcb[ucIndex].ucState = KEY_RELEASE;
			}
		}
#endif
	}
}

/*****************************************************************************
Function name : Read_KeyState
Description: 读取对应KeyId的键值
Input: KeyId->按键编号
Return: 返回按键状态
Notes:
******************************************************************************/
static uint8_t Read_KeyState(uint8_t KeyId)
{
	if (KeyId >= KEY_ID_MAX)
		return KEY_ERROR;

	return ((BSP_ReadKeyValue(KeyId) == 1) ? KEY_PUSH : KEY_RELEASE);
}

/**
 * @brief  APP_SetKeyDelay.
 * @note   None.
 * @param
 *		  KeyId:key index;
 *		  bState:true,false;
 * @retval bool.
 */
bool APP_KeyDelayConfig(uint8_t KeyId, bool bState)
{
	if (KeyId >= KEY_ID_MAX)
		return false;

	if (bState)
		s_stKeyTcb[KeyId].usLongTH = KEY_PUSH_10MSBASE350MS;
	else
		s_stKeyTcb[KeyId].usLongTH = KEY_PUSH_10MSBASE100MS;

	return true;
}

/**
 * @brief  APP_KeyReturnVal.
 * @note   None.
 * @param  KeyId:key index;
 * @retval .
 */
uint8_t APP_ReadKeyVal(uint8_t KeyId)
{
	if (KeyId >= KEY_ID_MAX)
		return 0xFF;

	return s_stKeyTcb[KeyId].ucTrigger;
}

/**
 * @brief  APP_IsKeyPush.
 * @note   None.
 * @param  None;
 * @retval bool.
 */
bool APP_IsKeyPush(void)
{
	for (uint8_t ucIndex = 0; ucIndex < KEY_ID_MAX; ucIndex++)
	{
		if (APP_ReadKeyVal(ucIndex) == LONG_PRO)
			return true;
	}
	return false;
}
