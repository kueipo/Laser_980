
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define FILTER_LONG     	0x03 //0b00000011
#define LOCK_PROTECT_FLAG "lock"

/* Configuration table -------------------------------------------------------*/
SafeLock_Struct s_stSafeLockerTcb[LOCK_ID_MAX];

/* Private Function prototypes -----------------------------------------------*/
static void Check_LockerState(uint8_t id);

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_SafeLock_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SafeLock_Init(void)
{	
	uint8_t data[LOCK_ID_MAX];
	/* flag */
	APP_Common_GetParameters(LOCK_PROTECT_FLAG, data, sizeof(data));
	for (uint8_t i = 0; i < LOCK_ID_MAX; i++)
	{
		s_stSafeLockerTcb[i].bState = true;
		s_stSafeLockerTcb[i].bProtect = data[i];
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
	for (uint8_t i = 0; i < LOCK_ID_MAX; i++)
	{
		Check_LockerState(i);
	}
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

	if (s_stSafeLockerTcb[id].bState)
		return SAFELOCK_CONN;
	else
		return SAFELOCK_DISCONN;
}

/**
 * @brief  APP_SafeLock_WritePROT.
 * @note   None.
 * @param
 *		  	id:locker index;
 *		  	bState:true, false;
 * @retval HandpieceState.
 */
void APP_SafeLock_WritePROT(uint8_t id, bool bState)
{
	if (id > LOCK_ID_MAX)
		return;
	
	if (s_stSafeLockerTcb[id].bProtect == bState)
		return;
	
	s_stSafeLockerTcb[id].bProtect = bState;
	
	uint8_t data[LOCK_ID_MAX];
	for (uint8_t i = 0; i < LOCK_ID_MAX; i++)
		data[i] = s_stSafeLockerTcb[id].bProtect;
	
	APP_Common_SaveParameters(LOCK_PROTECT_FLAG, data, sizeof(data));
}

/**
 * @brief  APP_SafeLock_ReadPROT.
 * @note   None.
 * @param  id:locker index;
 * @retval bProtect.
 */
bool APP_SafeLock_ReadPROT(uint8_t id)
{
	if (id > LOCK_ID_MAX)
		return false;

	return s_stSafeLockerTcb[id].bProtect;
}

/**
 * @brief  APP_SafeLock_IsErr.
 * @note   None.
 * @param  None.
 * @retval bool.
 */
bool APP_SafeLock_IsErr(void)
{
	for (uint8_t i = 0; i < LOCK_ID_MAX; i++)
	{
		if (s_stSafeLockerTcb[i].bProtect)
		{
			if (s_stSafeLockerTcb[i].bState == false)
			{
				return true;
			}
		}
	}
	return false;
}

/* Private Function prototypes -----------------------------------------------*/
/**
 * @brief  Check_LockerState.
 * @note   None.
 * @param  id.
 * @retval SafeLock ConnectState.
 */
static void Check_LockerState(uint8_t id)
{
	if (id >= LOCK_ID_MAX)
		return;
		
	s_stSafeLockerTcb[id].ucFilter <<= 1;
	s_stSafeLockerTcb[id].ucFilter |= BSP_SafeLock_State(id);
	
	uint8_t filter = s_stSafeLockerTcb[id].ucFilter & FILTER_LONG;
	if (filter == FILTER_LONG)
		s_stSafeLockerTcb[id].bState = true;
	else if (filter == 0x00)
		s_stSafeLockerTcb[id].bState = false;
}
