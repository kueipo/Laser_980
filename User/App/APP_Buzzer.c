
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define BUZZER_TIME		2

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
__IOM Buzzer_Struct s_stBuzzerTcb[BUZZER_ID_MAX] = 
{
	{
		.pEnv = "beep0",
	},
};

/* Function prototypes -------------------------------------------------------*/
static uint8_t APP_GetFlash(uint8_t id)
{
	uint8_t key[1] = {0};
		
	if (ef_get_env_blob(s_stBuzzerTcb[id].pEnv, key, sizeof(key) , NULL) )
		/* Get succeeded */
		;
	else	/* initialize variable */
		ef_set_env_blob(s_stBuzzerTcb[id].pEnv, key, sizeof(key));

	return key[0];
}

static void APP_SetFlash(uint8_t id, bool bState)
{
	/* Save Parameters */
	uint8_t key[1];
	
	key[0] = bState;
	
	ef_set_env_blob(s_stBuzzerTcb[id].pEnv, key, sizeof(key));
}

/**
 * @brief  APP_Buzzer_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Buzzer_Init(void)
{
/*	memset((uint8_t*)&s_stBuzzerTcb, 0, sizeof(s_stBuzzerTcb));	*/
	
	for (uint8_t id = 0; id < BUZZER_ID_MAX; id++)
	{
		APP_Buzzer_Config(id, false);
		s_stBuzzerTcb[id].bEnable = (bool)APP_GetFlash(id);
	}
	
	s_stBuzzerTcb[0].bEnable = true;
}

/**
 * @brief  APP_Buzzer_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Buzzer_Task(void)
{
	for (uint8_t index = 0; index < BUZZER_ID_MAX; index++)
	{
		if (s_stBuzzerTcb[index].bEnable == false)	// Do not execute
			continue;
		
		/*  if ucTime = ~0 */
		if (0xFF == s_stBuzzerTcb[index].ucTime)
			continue;
			
		if (s_stBuzzerTcb[index].ucTime)
			s_stBuzzerTcb[index].ucTime--;
		else
			APP_Buzzer_Config(index, false);
	}
}

/**
 * @brief  APP_Buzzer_Config.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_Buzzer_Config(uint8_t id, bool bState)
{
	if ((s_stBuzzerTcb[id].bState == bState) || (s_stBuzzerTcb[id].bEnable == false))
		return;
	
	s_stBuzzerTcb[id].bState = bState;
	
	BUZZER_OpMode_Tag mode;
	if (bState)
	{
		mode = BUZZER_ON;
		s_stBuzzerTcb[id].ucTime = BUZZER_TIME;
	}
	else
		mode = BUZZER_OFF;
	
	BSP_Buzzer_Operate(id, mode);
}

/**
 * @brief  APP_Buzzer_Long.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_Buzzer_Long(uint8_t id, bool bState)
{
	if (s_stBuzzerTcb[id].bEnable == false)
		return;
	
	BUZZER_OpMode_Tag mode;
	if (bState)
	{
		mode = BUZZER_ON;
		s_stBuzzerTcb[id].ucTime = 0xFF;
	}
	else
		mode = BUZZER_OFF;
	
	if (s_stBuzzerTcb[id].bState == bState)
		return;
	
	s_stBuzzerTcb[id].bState = bState;
	BSP_Buzzer_Operate(id, mode);
}

/**
 * @brief  APP_Buzzer_SetEnableBit.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_Buzzer_SetEnableBit(uint8_t id, bool bState)
{
	if (s_stBuzzerTcb[id].bEnable == bState)
		return;
	
	s_stBuzzerTcb[id].bEnable = bState;
	APP_SetFlash(id, bState);
}

/**
 * @brief  APP_Buzzer_GetEnableBit.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
bool APP_Buzzer_GetEnableBit(uint8_t id)
{
	return s_stBuzzerTcb[id].bEnable;
}
