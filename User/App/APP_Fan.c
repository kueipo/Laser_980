
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

#if IN_FAN_MAX_MUNBER || EX_FAN_MAX_MUNBER

/* Define --------------------------------------------------------------------*/
#define WORKING_MIN_TEMPERTATURE			25

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
uint16_t Speed[IN_FAN_MAX_MUNBER + EX_FAN_MAX_MUNBER] = {0};

FanModel_TypeDef s_stFanTcb[FAN_MODULE_MAX_NUMBER];

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_Fan_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Fan_Init(void)
{
	uint8_t i;
	for (i = 0; i < FAN_MODULE_MAX_NUMBER; i++)
	{
		s_stFanTcb[i].AutoPower = 1;
		s_stFanTcb[i].Power = 1;
	}
	
	/* internal fan -------------------------*/
#if IN_FAN_MAX_MUNBER
	s_stFanTcb[IN_FAN_MODULE].number = IN_FAN_MAX_MUNBER;
	s_stFanTcb[IN_FAN_MODULE].Speed = Speed + 0;
#endif
	
	/* external fan -------------------------*/
#if EX_FAN_MAX_MUNBER
	s_stFanTcb[EX_FAN_MODULE].number = EX_FAN_MAX_MUNBER;
	s_stFanTcb[EX_FAN_MODULE].Speed = Speed + IN_FAN_MAX_MUNBER;
#endif
}

/**
 * @brief  APP_Fan_Task.
 * @note   None.
 * @param  index.
 *		  	 powerval.
 * @retval None.
 */
void APP_Fan_Task(void)
{
	/* internal fan -------------------------*/
#if IN_FAN_MAX_MUNBER
	/* Read MOS temperature value */
	s_stFanTcb[IN_FAN_MODULE].Temperature = APP_Mos_ReadTemperature();
	/* Automatic speed regulation */
	s_stFanTcb[IN_FAN_MODULE].Power = ( s_stFanTcb[IN_FAN_MODULE].Temperature <= WORKING_MIN_TEMPERTATURE ? \
													0 : s_stFanTcb[IN_FAN_MODULE].Temperature >= (WORKING_MIN_TEMPERTATURE + 10) ? \
													10 : (s_stFanTcb[IN_FAN_MODULE].Temperature - WORKING_MIN_TEMPERTATURE) );
	
	BSP_Fan_Config(FAN_ID_0, (s_stFanTcb[IN_FAN_MODULE].Power * 10));
	
	BSP_Fan_Task();
	
#endif /* #if IN_FAN_MAX_MUNBER */
	
	/* external fan -------------------------*/
#if EX_FAN_MAX_MUNBER
	
#endif /* EX_FAN_MAX_MUNBER */
}

/**
 * @brief  FanPowerControl.
 * @note   None.
 * @param  index.
 *		  	 powerval.
 * @retval None.
 */
void FanPowerControl(FAN_MODULE_ENUM module, uint8_t powerval)
{
#if 0
	switch(module)
	{
		case 0:
			if (powerval)
			{
			//	DEV_FAN_0_POWER_SET(powerval);
			}
			else
			{
			//	DEV_FAN_0_DISABLE;
			}
			break;
		case 1:
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
#if 0
	FAN_MODULE_INDEX i;
	static uint8_t oldfanspeed[FAN_MODULE_NUMBER] = {0};
	for (i = FAN_MODULE_1; i < FAN_MODULE_NUMBER; i++)
	{
		/* Automatic speed regulation */
		if (s_stFanTcb[i].AutoPower)
		{
			s_stFanTcb[i].Power = ( s_stFanTcb[i].Temperature <= WORKING_MIN_TEMPERTATURE ? \
							0: s_stFanTcb[i].Temperature >= (WORKING_MIN_TEMPERTATURE+10) ? \
							10:(s_stFanTcb[i].Temperature - WORKING_MIN_TEMPERTATURE));
		}
		/* Manual speed regulation */
		
		/* The speed has changed */
		if (s_stFanTcb[i].Power != oldfanspeed[i])
		{
			oldfanspeed[i] = s_stFanTcb[i].Power;
			FanPowerControl(i, oldfanspeed[i]*10);
		}
	}
#endif
}

/**
 * @brief  Fan_OptPowerVal.
 * @note   None.
 * @param  opt.
 * @param  module.
 * @param  val.
 * @retval result.
 */
uint8_t Fan_OptPowerVal(Data_OPT opt, FAN_MODULE_ENUM module, uint8_t val)
{
	uint8_t result = 0;
	
	if (module >= FAN_MODULE_MAX_NUMBER)
		return result;

	switch (opt)
	{
	default:
	case READ:
		result = s_stFanTcb[module].Power;
		break;
	case WRITE:
		s_stFanTcb[module].Power = val;
		break;
	}
	return result;
}

/**
 * @brief  Write temperature value.
 * @note   None.
 * @param  opt.
 *		     module.
 *		     val.
 * @retval result.
 */
uint8_t Fan_OptTemperatureVal(Data_OPT opt, FAN_MODULE_ENUM module, uint8_t val)
{
	uint8_t result = 0;
	if (module >= FAN_MODULE_MAX_NUMBER)
		return result;

	switch (opt)
	{
	default:
	case READ:
		result = s_stFanTcb[module].Temperature;
		break;
	case WRITE:
		s_stFanTcb[module].Temperature = val;
		break;
	}
	return result;
}

/**
 * @brief  Fan_OptAutoPower.
 * @note   None.
 * @param  opt.
 *		     module.
 *		     val.
 * @retval result.
 */
uint8_t Fan_OptAutoPower(Data_OPT opt, FAN_MODULE_ENUM module, uint8_t val)
{
	uint8_t result = 0xFF;
	
	if (module >= FAN_MODULE_MAX_NUMBER)
		return result;

	switch (opt)
	{
	default:
	case READ:
		result = s_stFanTcb[module].AutoPower;
		break;
	case WRITE:
		s_stFanTcb[module].AutoPower = val;
		break;
	}
	return result;
}

/**
 * @brief  APP_Fan_OptSpeedVal.
 * @note   None.
 * @param  opt.
 *		     module.
 *		     val.
 * @retval result.
 */
uint16_t APP_Fan_OptSpeedVal(Data_OPT opt, FAN_MODULE_ENUM module, uint8_t id, uint16_t val)
{
	uint16_t result = 0;

	if (module >= FAN_MODULE_MAX_NUMBER || id >= s_stFanTcb[module].number)
		return result;

	switch (opt)
	{
	default:
	case READ:
		result = s_stFanTcb[module].Speed[id];
		break;
	case WRITE:
		s_stFanTcb[module].Speed[id] = val;
		break;
	}
	
	return result;
}

#endif
