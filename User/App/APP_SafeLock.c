
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Configuration table -------------------------------------------------------*/
__IOM SafeLock_Struct s_stSafeLockTcb[LOCK_ID_MAX];

/* Function prototypes -------------------------------------------------------*/
static uint8_t Read_LockPinState(uint8_t id);

/**
 * @brief  APP_SafeLock_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SafeLock_Init(void)
{
	uint8_t id;

	memset((uint8_t *)&s_stSafeLockTcb, 0, sizeof(s_stSafeLockTcb));

	for (id = 0; id < LOCK_ID_MAX; id++)
	{
		s_stSafeLockTcb[id].bState = false;
		s_stSafeLockTcb[id].bProtect = true;
	}
}

/**
 * @brief  APP_SafeLock_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SafeLock_Task(void)
{	
	uint8_t id;
	for (id = 0; id < LOCK_ID_MAX; id++)
	{
		if (Read_LockPinState(id) == true)
			s_stSafeLockTcb[id].bState = true;
		else
			s_stSafeLockTcb[id].bState = false;
	}
}

/**
 * @brief  Read_LockPinState.
 * @note   None.
 * @param  id.
 * @retval result.
 */
static uint8_t Read_LockPinState(uint8_t id)
{
    if (id >= LOCK_ID_MAX)
        return 0XFF;

	return	((BSP_SafeLock_ReadState(id) == true) ? true : false);
}

/**
 * @brief  APP_SafeLock_ReadConn.
 * @note   None.
 * @param  id.
 * @retval SafeLock ConnectState.
 */
uint8_t APP_SafeLock_ReadConn(uint8_t id)
{
	if (id >= LOCK_ID_MAX)
        return SAFELOCK_ERROR;
		
	if (s_stSafeLockTcb[id].bState)
		return SAFELOCK_CONN;
	else
		return SAFELOCK_DISCONN;
}

/**
 * @brief  APP_SafeLock_WritePROT.
 * @note   None.
 * @param  id:lock index;
 *		  	 st:true,false;
 * @retval bool.
 */
bool APP_SafeLock_WritePROT(uint8_t id, bool bState)
{
	if (id > LOCK_ID_MAX)
		return false;
	
	s_stSafeLockTcb[id].bProtect = bState;
	return true;
}

/**
 * @brief  APP_SafeLock_ReadPROT.
 * @note   None.
 * @param  id:lock index;
 * @retval bProtect.
 */
bool APP_SafeLock_ReadPROT(uint8_t id)
{
	if (id > LOCK_ID_MAX)
		return false;

	return s_stSafeLockTcb[id].bProtect;
}

/**
 * @brief  APP_SafeLock_IsErr.
 * @note   None.
 * @param  None.
 * @retval bool.
 */
bool APP_SafeLock_IsErr(void)
{
	for (uint8_t id = 0; id < LOCK_ID_MAX; id++)
	{
		if (s_stSafeLockTcb[id].bProtect)
		{
			if (s_stSafeLockTcb[id].bState == false)
				return true;
		}
	}
	return false;
}
