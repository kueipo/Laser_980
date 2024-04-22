
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
Motor_Struct s_stMotorTcb[MOTOR_ID_MAX];

/* Function prototypes -------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_Motor_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Motor_Init(void)
{
	for (uint8_t i = 0; i < MOTOR_ID_MAX; i++)
	{
		s_stMotorTcb[i].TH_L = 0;
		s_stMotorTcb[i].TH_H = 0xFFFF;
	}
}

/**
 * @brief  APP_Motor_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Motor_Task(void)
{
	for (uint8_t i = 0; i < MOTOR_ID_MAX; i++)
	{
		uint16_t speed = BSP_Motor_ReadSpeed(i);
		
		s_stMotorTcb[i].speed = speed;
		/* error */
		if (speed > s_stMotorTcb[i].TH_H || speed < s_stMotorTcb[i].TH_L)
		{
			/* close motor */
			BSP_Motor_WriteState(i, false);

			s_stMotorTcb[i].bError = true;
			/* UPD */

		}
		else
			s_stMotorTcb[i].bError = false;
	}
}

/**
 * @brief  APP_Motor_WriteThreshold.
 * @note   None.
 * @param  id.
 * @param  th_l.
 * @param  th_h.
 * @retval None.
 */
bool APP_Motor_WriteThreshold(uint8_t id, Motor_Struct *th)
{
	if (id >= MOTOR_ID_MAX)
		return false;

	s_stMotorTcb[id].TH_L = th->TH_L;
	s_stMotorTcb[id].TH_H = th->TH_H;

	return true;
}

/**
 * @brief  APP_Motor_ReadThreshold.
 * @note   None.
 * @param  id.
 * @retval *Motor_Struct.
 */
Motor_Struct *APP_Motor_ReadThreshold(uint8_t id)
{
	if (id >= MOTOR_ID_MAX)
		return 0;

	return &s_stMotorTcb[id];
}

/**
 * @brief  APP_Motor_IsError.
 * @note   None.
 * @param  id.
 * @retval err.
 */
bool APP_Motor_IsError(uint8_t id)
{
	if (id >= MOTOR_ID_MAX)
		return true;

	return s_stMotorTcb[id].bError;
}
