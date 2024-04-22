
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define WORKING_MIN_TEMPERTATURE			25

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
FanModel_TypeDef s_stFanTcb[FAN_MODULE_NUMBER];

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  Fan_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Fan_Init(void)
{
	uint8_t i, j;
	for (i = 0; i < FAN_MODULE_NUMBER; i++)
	{
		s_stFanTcb[i].AutoPower = 1;
		s_stFanTcb[i].Power = 1;
		for (j = 0; j < FAN_MAX_MUNBER; j++)
			s_stFanTcb[i].Speed[j] = 0;
	}
}

/**
 * @brief  FanPowerControl.
 * @note   None.
 * @param  index.
 *		  powerval.
 * @retval None.
 */
void FanPowerControl(uint8_t index, uint8_t powerval)
{
#if 0
	switch(index)
	{
		case FAN_MODULE_1:
			if (powerval)
			{
			//	DEV_FAN_0_POWER_SET(powerval);
			}
			else
			{
			//	DEV_FAN_0_DISABLE;
			}
			break;
		case FAN_MODULE_NUMBER:
		default:
			break;
	}
#endif
}

/**
 * @brief  Fan_Run.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void Fan_Run(void)
{
#if 1
	FAN_MODULE_INDEX i;
	static uint8_t oldfanspeed[FAN_MODULE_NUMBER] = {0};
	for (i = FAN_MODULE_1; i < FAN_MODULE_NUMBER; i++)
	{
		/* Automatic speed regulation */
		if (s_stFanTcb[i].AutoPower)
		{
			s_stFanTcb[i].Power = (s_stFanTcb[i].Temperature <= WORKING_MIN_TEMPERTATURE ? 0 : 
														s_stFanTcb[i].Temperature >= (WORKING_MIN_TEMPERTATURE + 10) ? 10	: 
														(s_stFanTcb[i].Temperature - WORKING_MIN_TEMPERTATURE));
		}
		/* Manual speed regulation */

		/* The speed has changed */
		if (s_stFanTcb[i].Power != oldfanspeed[i])
		{
			oldfanspeed[i] = s_stFanTcb[i].Power;
			FanPowerControl(i, oldfanspeed[i] * 10);
		}
	}
#endif
}

/**
 * @brief  Fan_OptPowerVal.
 * @note   None.
 * @param  opt.
 * @param  index.
 * @param  val.
 * @retval None.
 */
uint8_t Fan_OptPowerVal(Data_OPT opt, uint8_t index, uint8_t val)
{
	uint8_t result = 0;
	if (index >= FAN_MAX_MUNBER)
		return result;

	switch (opt)
	{
	default:
	case READ:
		result = s_stFanTcb[index].Power;
		break;
	case WRITE:
		s_stFanTcb[index].Power = val;
		break;
	}
	return result;
}

/**
 * @brief  Write temperature value.
 * @note   None.
 * @param  opt.
 * @param	 index.
 * @param	 val.
 * @retval None.
 */
uint8_t Fan_OptTemperatureVal(Data_OPT opt, uint8_t index, uint8_t val)
{
	uint8_t result = 0;
	if (index >= FAN_MAX_MUNBER)
		return result;

	switch (opt)
	{
	default:
	case READ:
		result = s_stFanTcb[index].Temperature;
		break;
	case WRITE:
		s_stFanTcb[index].Temperature = val;
		break;
	}
	return result;
}

/**
 * @brief  Fan_OptAutoPower.
 * @note   None.
 * @param  opt.
 * @param  index.
 * @param  val.
 * @retval None.
 */
uint8_t Fan_OptAutoPower(Data_OPT opt, uint8_t index, uint8_t val)
{
	uint8_t result = 0xFF;
	if (index >= FAN_MAX_MUNBER)
		return result;

	switch (opt)
	{
	default:
	case READ:
		result = s_stFanTcb[index].AutoPower;
		break;
	case WRITE:
		s_stFanTcb[index].AutoPower = val;
		break;
	}
	return result;
}

/**
 * @brief  Fan_OptAutoPower.
 * @note   None.
 * @param  opt.
 * @param  index.
 * @param  val.
 * @retval None.
 */
uint16_t APP_Fan_OptSpeedVal(Data_OPT opt, uint8_t module, uint8_t index, uint16_t val)
{
	uint16_t result = 0;

	if (module >= FAN_MODULE_NUMBER || index >= FAN_MAX_MUNBER)
		return result;

	switch (opt)
	{
	default:
	case READ:
		result = s_stFanTcb[module].Speed[index];
		break;
	case WRITE:
		s_stFanTcb[module].Speed[index] = val;
		break;
	}
	return result;
}
