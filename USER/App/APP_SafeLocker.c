
#include "APP/APP_Common.h"

__IOM SafeLocker_Struct s_stSafeLockerTcb[LOCKER_ID_MAX];

static uint8_t Read_LockerPinState(uint8_t ucLockerId);

/*****************************************************************************
Function name : APP_SafeLocker_Init
Description: 
Input: NONE		
Return: NONE     
Notes:
******************************************************************************/
void APP_SafeLocker_Init(void)
{
  uint8_t ucIndex;
    
   memset((uint8_t*)&s_stSafeLockerTcb, 0, sizeof(s_stSafeLockerTcb));
    
  for (ucIndex = 0; ucIndex < LOCKER_ID_MAX ;ucIndex++)
  {
		s_stSafeLockerTcb[ucIndex].bState = false;
		s_stSafeLockerTcb[ucIndex].bProtect = true;
  }
}

/*****************************************************************************
Function name : APP_SafeLocker_Task
Description: 
Input: NONE		
Return: NONE     
Notes:
******************************************************************************/
void APP_SafeLocker_Task(void)
{	
	uint8_t ucIndex;
	for (ucIndex = 0; ucIndex < LOCKER_ID_MAX; ucIndex++)
	{
		if ( Read_LockerPinState(ucIndex) == true )
			s_stSafeLockerTcb[ucIndex].bState = true;
		else
			s_stSafeLockerTcb[ucIndex].bState = false;
	}
}

/*****************************************************************************
Function name : Read_HandpiecePinState
Description: 
Input: LockerId-
Return:  
Notes:
******************************************************************************/
static uint8_t Read_LockerPinState(uint8_t ucLockerId)
{
  if (ucLockerId >= LOCKER_ID_MAX)
    return 0XFF;

	return	((BSP_SafeLockerValue(ucLockerId) == true) ? true : false);
}

/**
* @brief  APP_ReadSafeLockerConn.
* @note   None.
* @param  LockerId.
* @retval SafeLock ConnectState.
*/
uint8_t APP_ReadSafeLockerConn(uint8_t ucLockerId)
{
	if (ucLockerId >= LOCKER_ID_MAX)
		return SAFELOCKER_ERROR;

	if (s_stSafeLockerTcb[ucLockerId].bState)
		return SAFELOCKER_CONN;
	else
		return SAFELOCKER_DISCONN;
}

/**
* @brief  APP_WriteSafeLockerPROT.
* @note   None.
* @param  
*		  LockerId:locker index;
*		  st:true,false;
* @retval HandpieceState.
*/
void APP_WriteSafeLockerPROT(uint8_t ucLockerId, bool bState)
{
	if (ucLockerId > LOCKER_ID_MAX)
		return;
	
	s_stSafeLockerTcb[ucLockerId].bProtect = bState;
}

/**
* @brief  APP_ReadSafeLockerPROT.
* @note   None.
* @param  
*		  LockerId:locker index;
* @retval bProtect.
*/
bool APP_ReadSafeLockerPROT(uint8_t ucLockerId)
{
	if (ucLockerId > LOCKER_ID_MAX)
		return false;
	
	return s_stSafeLockerTcb[ucLockerId].bProtect;
}

/**
* @brief  APP_IsSafeLockErr.
* @note   
* @param  None.
* @retval 
*/
bool APP_IsSafeLockErr(void)
{
	for (uint8_t ucIndex = 0; ucIndex < LOCKER_ID_MAX; ucIndex++)
	{
		if (s_stSafeLockerTcb[ucIndex].bProtect)
		{
			if (s_stSafeLockerTcb[ucIndex].bState == false)
			{
				return true;
			}
		}
	}
	return false;
}
