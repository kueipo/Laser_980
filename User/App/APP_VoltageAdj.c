
/* Includes ------------------------------------------------------------------*/
#include "APP_Common.h"

/* Define --------------------------------------------------------------------*/
/* #define MAX5400 */
#define AD840X
#define BAR_FLAG	"barNum"

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
/*
 *	V = (2.5/4095)*N*(8.2/108.2)
 *	VoltageADC = V/8
 *	-0.3V
 */
const uint16_t VoltageADC[] = 
{
/*	1900V		 */
	2412, 2437, 15, \
/*	2300V		 */	
	2850, 2870, 35, \
/*	2700V		 */	
	3350, 3370, 40,
};
static const uint8_t VoltageAdcNumber = sizeof(VoltageADC) / sizeof(VoltageADC[0]);

typedef struct 
{
	__IO uint16_t	usTH_L;
	__IO uint16_t	usTH_H;
	__IO uint16_t	usSetVal;
	__IO uint16_t	usMaxVal;
	__IO uint8_t	ucBarNum;
	__IO bool		bError;
	
}VolAdj_Struct;

VolAdj_Struct s_stVolAdjTcb = {0};

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_Voltae_Init.
 * @note   None.
 * @param  vol.
 * @retval	None.
 */
void APP_Voltage_Init(void)
{
	uint8_t tmp;
//	s_stVolAdjTcb.usTH_L = VoltageADC[0];
//	s_stVolAdjTcb.usTH_H = VoltageADC[1];
//	s_stVolAdjTcb.usMaxVal = VoltageADC[2];
	s_stVolAdjTcb.usSetVal = 0;
	s_stVolAdjTcb.bError = true;

	APP_VoltageAdj(0);

	/* read number of the bar from flash */
	uint8_t barnum[2] = {0};

	if (ef_get_env_blob(BAR_FLAG, barnum, sizeof(barnum), NULL))
	{
		s_stVolAdjTcb.ucBarNum = barnum[0];
	}
	else
	{
		tmp = 12;
		s_stVolAdjTcb.ucBarNum = tmp;
		ef_set_env_blob(BAR_FLAG, &tmp, sizeof(tmp));
	}

	APP_VoltageConfig(s_stVolAdjTcb.ucBarNum);
}

/**
 * @brief  APP_VoltageAdj.
 * @note   None.
 * @param  vol.
 * @retval	None.
 */
void APP_VoltageAdj(uint8_t vol)
{
#if 0
	if (s_stVolAdjTcb.bVol == vol)
	{
		return;
	}
#endif

#if defined(MAX5400)
	Max5400_WriteByte(vol);
#elif defined(AD840X)
	AD840X_WriteByte(0x00, vol);
#endif
}

/**
 * @brief  APP_VoltageConfig.
 * @note   None.
 * @param  vol.
 * @retval	None.
 */
void APP_VoltageConfig(uint8_t num)
{

	uint8_t index;
	switch (num)
	{
	default:
		num = 10;
	case 10:
		index = 0;
		break;
	case 12:
		index = 1;
		break;
	case 14:
		index = 2;
		break;
	}

	if (num != s_stVolAdjTcb.ucBarNum)
	{
		/* write flash */
		ef_set_env_blob(BAR_FLAG, &num, sizeof(num));
		APP_Voltage_OptBarNum(WRITE, num);
	}

	/* Prevent overflow */
	if ((index * 3 + 2) < VoltageAdcNumber)
	{
		s_stVolAdjTcb.usTH_L = VoltageADC[index * 3];
		s_stVolAdjTcb.usTH_H = VoltageADC[index * 3 + 1];
		s_stVolAdjTcb.usMaxVal = VoltageADC[index * 3 + 2];
	}
}

/**
 * @brief  APP_Voltage_Task.
 * @note   None.
 * @param  None.
 * @retval	None.
 */
void APP_Voltage_Task(void)
{
	uint16_t PumpVolADC = BSP_ReadADCVal(V27_VOL_CHNL);
	uint16_t threshold_H = s_stVolAdjTcb.usTH_H;
	uint16_t threshold_L = s_stVolAdjTcb.usTH_L;

	/* Laser is Running, return */
	if (APP_IsLaserRunning())
		return;

	s_stVolAdjTcb.bError = true;

	/* voltage over */
	if (PumpVolADC > threshold_H)
	{
		if (s_stVolAdjTcb.usSetVal)
		{
			s_stVolAdjTcb.usSetVal--;
			goto refreshVoltage;
		}
		else
		{
			/* error:voltage over */
		}
	}
	/* voltage low */
	else if (PumpVolADC < threshold_L)
	{
		if (s_stVolAdjTcb.usSetVal < s_stVolAdjTcb.usMaxVal)
		{
			s_stVolAdjTcb.usSetVal++;
			goto refreshVoltage;
		}
		else
		{
			/* error:voltage low */
		}
	}
	/* voltage OK */
	else
	{
		s_stVolAdjTcb.bError = false;
	}
	return;

refreshVoltage:
	APP_VoltageAdj(s_stVolAdjTcb.usSetVal);
}

/**
 * @brief  APP_IsVoltageErr.
 * @note   Voltage error.
 * @param  None.
 * @retval error.
 */
bool APP_IsVoltageErr(void)
{
	return s_stVolAdjTcb.bError;
}

/**
 * @brief  APP_Voltage_ReadBarNum.
 * @note   Read bar number.
 * @param  None.
 * @retval ucBarNum.
 */
uint8_t APP_Voltage_ReadBarNum(void)
{
	return s_stVolAdjTcb.ucBarNum;
}

/**
 * @brief  APP_Voltage_OptBarNum.
 * @note   None.
 * @param  opt.
 * @param  num.
 * @retval result.
 */
uint8_t APP_Voltage_OptBarNum(Data_OPT opt, uint8_t num)
{
	uint8_t result = 0xFF;

	switch (opt)
	{
	default:
		break;
	case READ:
		result = s_stVolAdjTcb.ucBarNum;
		break;
	case WRITE:
		s_stVolAdjTcb.ucBarNum = num;
		break;
	}
	return result;
}
