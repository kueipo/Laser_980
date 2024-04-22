
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Configuration table -------------------------------------------------------*/
__IOM SafeLocker_Struct s_stSafeLockerTcb[LOCKER_ID_MAX];

/* Function prototypes -------------------------------------------------------*/
static uint8_t Read_LockerPinState(uint8_t id);

/**
 * @brief  APP_SafeLocker_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SafeLocker_Init(void)
{
	uint8_t index;

	memset((uint8_t *)&s_stSafeLockerTcb, 0, sizeof(s_stSafeLockerTcb));

	for (index = 0; index < LOCKER_ID_MAX; index++)
	{
		s_stSafeLockerTcb[index].bState = false;
		s_stSafeLockerTcb[index].bProtect = true;
	}
}

/**
 * @brief  APP_SafeLocker_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SafeLocker_Task(void)
{	
	uint8_t index;
	for (index = 0; index < LOCKER_ID_MAX; index++)
	{
		if (Read_LockerPinState(index) == true)
			s_stSafeLockerTcb[index].bState = true;
		else
			s_stSafeLockerTcb[index].bState = false;
	}
}

static uint8_t Read_LockerPinState(uint8_t id)
{
    if (id >= LOCKER_ID_MAX)
        return 0XFF;

	return	((BSP_SafeLockerValue(id) == true) ? true : false);
}

/**
 * @brief  APP_ReadSafeLockerConn.
 * @note   None.
 * @param  id.
 * @retval SafeLock ConnectState.
 */
uint8_t APP_ReadSafeLockerConn(uint8_t id)
{
	if (id >= LOCKER_ID_MAX)
        return SAFELOCKER_ERROR;
		
	if (s_stSafeLockerTcb[id].bState)
		return SAFELOCKER_CONN;
	else
		return SAFELOCKER_DISCONN;
}

/**
 * @brief  APP_WriteSafeLockerPROT.
 * @note   None.
 * @param
 *		  	id:locker index;
 *		  	st:true,false;
 * @retval bool.
 */
bool APP_WriteSafeLockerPROT(uint8_t id, bool bState)
{
	if (id > LOCKER_ID_MAX)
		return false;
	
	s_stSafeLockerTcb[id].bProtect = bState;
	return true;
}

/**
 * @brief  APP_ReadSafeLockerPROT.
 * @note   None.
 * @param
 *		  	id:locker index;
 * @retval bProtect.
 */
bool APP_ReadSafeLockerPROT(uint8_t id)
{
	if (id > LOCKER_ID_MAX)
		return false;

	return s_stSafeLockerTcb[id].bProtect;
}

/**
 * @brief  APP_IsSafeLockErr.
 * @note   None.
 * @param  None.
 * @retval bool.
 */
bool APP_IsSafeLockErr(void)
{
	for (uint8_t index = 0; index < LOCKER_ID_MAX; index++)
	{
		if (s_stSafeLockerTcb[index].bProtect)
		{
			if (s_stSafeLockerTcb[index].bState == false)
				return true;
		}
	}
	return false;
}