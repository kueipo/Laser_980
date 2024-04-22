
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

__IOM Handpiece_Struct s_stHandpieceTcb[HANDPIECE_ID_MAX];

static uint8_t Read_HandpiecePinState(uint8_t HandpieceId);

/*****************************************************************************
Function name : APP_KEY_Init
Description: APP Key 模块的初始化函数，在程序上电初始化的时候调用。	 
Input: NONE		
Return: NONE     
Notes:
******************************************************************************/
void APP_Handpiece_Init(void)
{
    uint8_t ucIndex;
    
    memset((uint8_t*)&s_stHandpieceTcb, 0, sizeof(s_stHandpieceTcb));
    
    for (ucIndex = 0; ucIndex < HANDPIECE_ID_MAX ;ucIndex++)
    {
		s_stHandpieceTcb[ucIndex].bState = false;
		s_stHandpieceTcb[ucIndex].bProtect = true;
    }
}

/*****************************************************************************
Function name : APP_KEY_Task
Description: APP Key模块的任务，在HCI_Task中当HCI_KEY事件被置位的时候，将被执行。
Input: NONE		
Return: NONE     
Notes:
******************************************************************************/
void APP_Handpiece_Task(void)
{	
	uint8_t ucIndex;
	for (ucIndex = 0; ucIndex < HANDPIECE_ID_MAX; ucIndex++)
	{
		/* 手柄正常连接 */
		if (Read_HandpiecePinState(ucIndex) == HANDPIECE_CONN)
			s_stHandpieceTcb[ucIndex].bState = true;
		/* 手柄断开 */
		else
			s_stHandpieceTcb[ucIndex].bState = false;
	}
}

/*****************************************************************************
Function name : Read_HandpiecePinState
Description: 读取对应HandpieceId的PIN状态
Input: HandpieceId->hand编号
Return: 返回PIN状态     
Notes:
******************************************************************************/
static uint8_t Read_HandpiecePinState(uint8_t HandpieceId)
{
    if (HandpieceId >= HANDPIECE_ID_MAX)
        return HANDPIECE_ERROR;

	return	((BSP_ReadHandpieceValue(HandpieceId) == 1) ? HANDPIECE_CONN : HANDPIECE_DISCONN);
}

/**
* @brief  APP_ReadHandpieceCONN.
* @note   None.
* @param  LockerId.
* @retval SafeLock ConnectState.
*/
uint8_t APP_ReadHandpieceCONN(uint8_t HandpieceId)
{
    if (HandpieceId >= HANDPIECE_ID_MAX)
        return HANDPIECE_ERROR;

	if (s_stHandpieceTcb[HandpieceId].bState == true)
		return HANDPIECE_CONN;
	else
		return HANDPIECE_DISCONN;
}

/**
* @brief  APP_WriteHandpiecePROT.
* @note   None.
* @param  HandpieceId, st.
* @retval HandpieceState.
*/
void APP_WriteHandpiecePROT(uint8_t HandpieceId, bool bState)
{
	if (HandpieceId >= HANDPIECE_ID_MAX)
        return;
	
	s_stHandpieceTcb[HandpieceId].bProtect = bState;
}

/**
* @brief  APP_IsHandpieceError.
* @note   None.
* @param  HandpieceId.
* @retval 返回手柄状态.
*/
bool APP_IsHandpieceError(void)
{
	uint8_t ucIndex;
	for (ucIndex = 0; ucIndex < HANDPIECE_ID_MAX; ucIndex++)
	{
		if (s_stHandpieceTcb[ucIndex].bProtect)
		{
			if (s_stHandpieceTcb[ucIndex].bState == false)
				return true;
		}
	}
	return false;
}
