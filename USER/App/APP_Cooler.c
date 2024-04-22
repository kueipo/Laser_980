
/* Includes ------------------------------------------------------------------*/
#include "APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define USING_CC6920SO_40A
#define COOLER_INX_FLAG "Cooler"

__IOM CoolerModel_Struct s_stCoolerTcb[COOLER_ID_MAX];

static uint8_t CoolerCurrent_Detection(void);
static uint16_t CoolerVoltage_Detection(void);
/*****************************************************************************
Function name : APP_LED_Init
Description: APP LED 模块的初始化函数，在程序上电初始化的时候调用。
Input: NONE
Return: NONE
Notes:
******************************************************************************/
void APP_Cooler_Init(void)
{
	memset((uint8_t *)&s_stCoolerTcb, 0, sizeof(s_stCoolerTcb));
#if 0
	s_stCoolerTcb.Current = 0;
	s_stCoolerTcb.Voltage = 0;
#endif

	/* read  Current information from flash */
	uint8_t temp[1] = {0};
	if (ef_get_env_blob(COOLER_INX_FLAG, temp, sizeof(temp), NULL))
	{
		s_stCoolerTcb[COOLER_0].ucCurrent = temp[0];
	}
	else
	{
		temp[0] = 0;
		s_stCoolerTcb[COOLER_0].ucCurrent = temp[0];
		ef_set_env_blob(COOLER_INX_FLAG, temp, sizeof(temp));
	}
}

/*****************************************************************************
Function name : APP_LED_Task
Description: APP LED模块的任务，在HCI_Task中当HCI_LED事件被置位的时候，将被执行。
Input: NONE
Return: NONE
Notes:
******************************************************************************/
void APP_Cooler_Task(void)
{
	static uint8_t ucIndex = 0;

	switch (ucIndex)
	{
	case COOLER_CURRENT:
		s_stCoolerTcb[COOLER_0].ucCurrent = CoolerCurrent_Detection();
		break;

	case COOLER_VOLTAGE:
		s_stCoolerTcb[COOLER_0].uiVoltage = CoolerVoltage_Detection();
		break;

	default:
		break;
	}

	if (++ucIndex >= COOLER_TASK_MAX)
		ucIndex = 0;
}

/**
 * @brief  CoolerCurrent_Detection.
 * @note   None.
 * @param  None.
 * @retval CURRENT VAL.
 */
static uint8_t CoolerCurrent_Detection(void)
{
	uint32_t CoolerCurADC = s_stCoolerTcb[COOLER_0].ucCurrent;

	if (s_stCoolerTcb[COOLER_0].ucPower >= 32)
	{
		CoolerCurADC = BSP_ReadADCVal(COOLER_CUR_CHNL);

		CoolerCurADC = ABS_RETURN(CoolerCurADC, 1650);
		if (CoolerCurADC < 20)
			CoolerCurADC = 0;

		CoolerCurADC *= 15;

#ifdef USING_CC6902SO_10A
		CoolerCurADC >>= 1;
#elif defined(USING_CC6902SO_10A)
		CoolerCurADC >>= 2;
#elif defined(USING_CC6920SO_40A)
		CoolerCurADC <<= 1;
#endif

		CoolerCurADC /= 100;
	}

	return (uint8_t)CoolerCurADC;
}

/**
 * @brief  CoolerVoltage_Detection.
 * @note   None.
 * @param  None.
 * @retval Voltage VAL.
 */
static uint16_t CoolerVoltage_Detection(void)
{
	uint32_t CoolerVolADC = BSP_ReadADCVal(V12_VOL_CHNL);

	CoolerVolADC *= 1320;
	CoolerVolADC /= BSP_ReadADCVal(ADC_VREF_CHNL);

	return (uint16_t)CoolerVolADC;
}

/**
 * @brief  APP_CoolerConfig.
 * @note   None.
 * @param  ucPowerOut:0-32.
 * @retval None.
 */
bool APP_CoolerConfig(uint8_t ucCoolerId, uint8_t ucPowerOut)
{
	uint16_t pwmout;

	if (ucCoolerId >= COOLER_ID_MAX)
		return false;

	if (s_stCoolerTcb[ucCoolerId].ucPower == ucPowerOut)
		return true;

	BSP_Cooler_Operate(ucCoolerId, COOLER_OFF);

	/* When the maximum power is exited, the current data is saved */
	if ((s_stCoolerTcb[ucCoolerId].ucPower == 32) && (ucPowerOut != 32))
	{
		/* save index of led */
		uint8_t tmp[1] = {0};

		tmp[0] = s_stCoolerTcb[ucCoolerId].ucCurrent;

		/* write flash */
		ef_set_env_blob(COOLER_INX_FLAG, tmp, sizeof(tmp));
	}

	if (ucPowerOut == 0)
	{
		s_stCoolerTcb[ucCoolerId].ucPower = ucPowerOut;
		s_stCoolerTcb[ucCoolerId].bRun = false;
	}
	else
	{
		s_stCoolerTcb[ucCoolerId].ucPower = ucPowerOut;

		pwmout = ucPowerOut * 100;

		if (ucPowerOut >= 32)
			pwmout += 1;

		BSP_Cooler_Config(ucCoolerId, pwmout);
		BSP_Cooler_Operate(ucCoolerId, COOLER_ON);
		s_stCoolerTcb[ucCoolerId].bRun = true;
	}
	return true;
}

/**
 * @brief  APP_ReadCoolerState.
 * @note   None.
 * @param  None.
 * @retval bState.
 */
bool APP_ReadCoolerState(uint8_t ucCoolerId)
{
	if (ucCoolerId >= COOLER_ID_MAX)
		return true;

	return s_stCoolerTcb[ucCoolerId].bRun;
}

/**
 * @brief  APP_ReadCoolerVoltage.
 * @note   None.
 * @param  CoolerId.
 * @retval uiVoltage.
 */
uint16_t APP_ReadCoolerVoltage(uint8_t ucCoolerId)
{
	return s_stCoolerTcb[ucCoolerId].uiVoltage;
}

/**
 * @brief  APP_ReadCoolerCurrent.
 * @note   None.
 * @param  CoolerId.
 * @retval ucCurrent.
 */
uint8_t APP_ReadCoolerCurrent(uint8_t ucCoolerId)
{
	return s_stCoolerTcb[ucCoolerId].ucCurrent;
}

/**
 * @brief  APP_ReadCoolerPower.
 * @note   None.
 * @param  CoolerId.
 * @retval ucCurrent.
 */
uint8_t APP_ReadCoolerPower(uint8_t ucCoolerId)
{
	return s_stCoolerTcb[ucCoolerId].ucPower;
}
