#include "Fan.h"
#include "DEV_Config.h"

/**
* Macro Definition
*/
#define WORKING_MIN_TEMPERTATURE			25

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/**
* Function Ceclaration
*/

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/**
* Variable Definition
*/
typedef struct {
	uint8_t AutoPower:1;
	uint8_t Power;
	uint8_t Temperature;
} FanModel_TypeDef;
FanModel_TypeDef FanModule[FAN_MODULE_NUMBER];

/* --------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------- */
/**
* Function Definition
*/

/**
* @brief  Fan_Init.
* @note   None.
* @param  None.
* @retval None.
*/
void Fan_Init(void)
{
	uint8_t i;
	for(i=0;i<FAN_MODULE_NUMBER;i++)
	{
		FanModule[i].AutoPower = 1;
		FanModule[i].Power = 1;
	}
}

/**
* @brief  FanPowerControl.
* @note   None.
* @param  index.
*					powerval.
* @retval None.
*/
void FanPowerControl(FAN_MODULE_INDEX index, uint8_t powerval)
{
	switch(index)
	{
		case FAN_MODULE_1:
			if (powerval) { DEV_FAN_0_POWER_SET(powerval); }
			else { DEV_FAN_0_DISABLE; }
			break;
		case FAN_MODULE_2:
			if (powerval) {	DEV_FAN_1_POWER_SET(powerval); }
			else { DEV_FAN_1_DISABLE;	}
			break;
		case FAN_MODULE_NUMBER:
		default:
			break;
	}
}

/**
* @brief  Fan_Run.
* @note   None.
* @param  None.
* @retval None.
*/
void Fan_Run(void)
{
	FAN_MODULE_INDEX i;
	static uint8_t oldfanspeed[FAN_MODULE_NUMBER] = {0};
	for(i=FAN_MODULE_1; i<FAN_MODULE_NUMBER; i++)
	{
		/* Automatic speed regulation */
		if (FanModule[i].AutoPower)
		{
			FanModule[i].Power = ( FanModule[i].Temperature <= WORKING_MIN_TEMPERTATURE ? \
														0: FanModule[i].Temperature >= (WORKING_MIN_TEMPERTATURE+10) ? \
														10:(FanModule[i].Temperature - WORKING_MIN_TEMPERTATURE));
		}
		/* Manual speed regulation */
		else	{;}
		
		/* The speed has changed */
		if (FanModule[i].Power != oldfanspeed[i])
		{
			oldfanspeed[i] = FanModule[i].Power;
			FanPowerControl(i, oldfanspeed[i]*10);
		}
		else	{;}
	}
}

/**
* @brief  FanModule_OptPowerVal.
* @note   None.
* @param  opt.
*					index.
*					val.
* @retval None.
*/
uint8_t FanModule_OptPowerVal(FAN_OPT opt, FAN_MODULE_INDEX index, uint8_t val)
{
	uint8_t result = 0;
	switch(opt)
	{
		default:
		case READ:
			result = FanModule[index].Power;
			break;
		case WRITE:
			FanModule[index].Power = val;
			break;
	}
	return result;
}

/**
* @brief  Write temperature value.
* @note   None.
* @param  opt.
*					index.
*					val.
* @retval None.
*/
uint8_t FanModule_OptTemperatureVal(FAN_OPT opt, FAN_MODULE_INDEX index, uint8_t val)
{
	uint8_t result = 0;
	switch(opt)
	{
		default:
		case READ:
			result = FanModule[index].Temperature;
			break;
		case WRITE:
			FanModule[index].Temperature = val;
			break;
	}
	return result;
}

/**
* @brief  FanModule_OptAutoPower.
* @note   None.
* @param  opt.
*					index.
*					val.
* @retval None.
*/
uint8_t FanModule_OptAutoPower(FAN_OPT opt, FAN_MODULE_INDEX index, uint8_t val)
{
	uint8_t result = 0;
	switch(opt)
	{
		default:
		case READ:
			result = FanModule[index].AutoPower;
			break;
		case WRITE:
			FanModule[index].AutoPower = val;
			break;
	}
	return result;
}


