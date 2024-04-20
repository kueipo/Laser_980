
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

__IOM Handpiece_Struct s_stHandpieceTcb[HANDPIECE_ID_MAX];

static uint8_t Read_HandpiecePinState(uint8_t id);

/**
 * @brief  APP_Handpiece_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Handpiece_Init(void)
{
	uint8_t index;

	memset((uint8_t *)&s_stHandpieceTcb, 0, sizeof(s_stHandpieceTcb));

	for (index = 0; index < HANDPIECE_ID_MAX; index++)
	{
		s_stHandpieceTcb[index].bState = false;
		s_stHandpieceTcb[index].bProtect = true;
	}
}

/**
 * @brief  APP_Handpiece_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Handpiece_Task(void)
{
	uint8_t index;
	for (index = 0; index < HANDPIECE_ID_MAX; index++)
	{
		/* connect */
		if (Read_HandpiecePinState(index) == HANDPIECE_CONN)
			s_stHandpieceTcb[index].bState = true;
		/* disconnect */
		else
			s_stHandpieceTcb[index].bState = false;
	}
}

/**
 * @brief  APP_ReadHandpieceCONN.
 * @note   None.
 * @param  ucHandpieceId.
 * @retval ConnectState.
 */
uint8_t APP_ReadHandpieceCONN(uint8_t id)
{
	if (id >= HANDPIECE_ID_MAX)
		return HANDPIECE_ERROR;

	if (s_stHandpieceTcb[id].bState == true)
		return HANDPIECE_CONN;
	else
		return HANDPIECE_DISCONN;
}

/**
 * @brief  APP_WriteHandpiecePROT.
 * @note   None.
 * @param  id, st.
 * @retval bool.
 */
bool APP_WriteHandpiecePROT(uint8_t id, bool bState)
{
	if (id >= HANDPIECE_ID_MAX)
		return false;

	s_stHandpieceTcb[id].bProtect = bState;
	
	return true;
}

/**
 * @brief  APP_IsHandpieceError.
 * @note   None.
 * @param  id.
 * @retval bool.
 */
bool APP_IsHandpieceError(void)
{
	uint8_t index;
	for (index = 0; index < HANDPIECE_ID_MAX; index++)
	{
		if (s_stHandpieceTcb[index].bProtect)
		{
			if (s_stHandpieceTcb[index].bState == false)
				return true;
		}
	}
	return false;
}

/**
 * @brief  Read_HandpiecePinState.
 * @note   None.
 * @param  ucHandpieceId.
 * @retval sate.
 */
static uint8_t Read_HandpiecePinState(uint8_t id)
{
	if (id >= HANDPIECE_ID_MAX)
		return HANDPIECE_ERROR;

	return ((BSP_ReadHandpieceValue(id) == 1) ? HANDPIECE_CONN : HANDPIECE_DISCONN);
}
