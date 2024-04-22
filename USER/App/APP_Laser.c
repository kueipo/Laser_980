
/* Includes ------------------------------------------------------------------*/
#include "APP_Common.h"
#include "DEV_Config.h"

/* Define --------------------------------------------------------------------*/
enum LASER_ERR_CODE{
	ERROR_NO = 0x00,
	ERROR_VOLTAGE_OVER = 0x01,
	ERROR_CURRENT_OVER = 0x02,
	ERROR_TIME_OVER = 0x04,
};

/* Function prototypes -------------------------------------------------------*/	
// -----------------------------------------------------------------------------
typedef struct 
{	
	volatile uint16_t usPulserWidth;
	ThresholdTypeDef stCurThreshold;
	ThresholdTypeDef stVolThreshold;
	volatile uint16_t usVolAdc;
	volatile uint8_t ucErrCode;
	volatile bool bError;
	volatile bool	bRun;
} Laser_Struct;

Laser_Struct s_stLaserTcb =
{
	.usPulserWidth = 0xFFFF,
	.stCurThreshold = 
		{
			.high = 0XFFFF,
			.low = 0,
		},
	.stVolThreshold = 
		{
			.high = 0XFFFF,
			.low = 0,
		},
};

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  FanPowerVal.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Laser_Init(void)
{
	APP_LaserOutEnable(true);
	
//	APP_Laser_WritePulseWidth(0XFFFF);
//	APP_Laser_WriteCurThreshold(0XFFFF, 0);
}

void APP_Laser_Task(void)
{
	uint16_t volADC = BSP_ReadADCVal(LASER_VOL_CHNL);
	uint16_t threshold_H = s_stLaserTcb.stVolThreshold.high;
	uint16_t threshold_L = s_stLaserTcb.stVolThreshold.low;
		
	s_stLaserTcb.ucErrCode |= ERROR_VOLTAGE_OVER;
	
	s_stLaserTcb.usVolAdc += volADC;
	s_stLaserTcb.usVolAdc >>= 1;
		
	/* Voltage Over */
	if (s_stLaserTcb.usVolAdc > threshold_H || s_stLaserTcb.usVolAdc < threshold_L )
	{
		/* Error:Voltage Over */
		/* Error:Voltage Low */
	}
	/* Voltage OK */
	else
	{
		s_stLaserTcb.ucErrCode &= ~ERROR_VOLTAGE_OVER;
	}
}

/**
 * @brief  APP_LaserOutEnable.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_LaserOutEnable(bool bState)
{
	if (bState == s_stLaserTcb.bRun)
		return;
		
	s_stLaserTcb.bRun = bState;

	BSP_Laser_Enable(bState);
}

// -----------------------------------------------------------------------------
/**
 * @brief  APP_Laser_WritePulseWidth.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_Laser_WritePulseWidth(uint16_t width)
{
	s_stLaserTcb.usPulserWidth = width;
	
	BSP_Laser_TimSet(width);
}

/**
 * @brief  APP_Laser_ReadPulseWidth.
 * @note   None.
 * @param  None.
 * @retval PulserWidth.
 */
uint16_t APP_Laser_ReadPulseWidth(void)
{
	return s_stLaserTcb.usPulserWidth;
}

// -----------------------------------------------------------------------------
/**
 * @brief  APP_Laser_WriteCurThreshold.
 * @note   None.
 * @param  high, low.
 * @retval None.
 */
void APP_Laser_WriteCurThreshold(uint16_t high, uint16_t low)
{
	s_stLaserTcb.stCurThreshold.high = high;
	s_stLaserTcb.stCurThreshold.low = low;

	BSP_Laser_AdcWDGSet(high, low);
}

/**
 * @brief  APP_Laser_ReadCurThreshold.
 * @note   None.
 * @param  None.
 * @retval *CurThreshold.
 */
ThresholdTypeDef * APP_Laser_ReadCurThreshold(void)
{
	return &s_stLaserTcb.stCurThreshold;
}

// -----------------------------------------------------------------------------
/**
 * @brief  APP_Laser_WriteVolThreshold.
 * @note   None.
 * @param  high, low.
 * @retval None.
 */
void APP_Laser_WriteVolThreshold(uint16_t high, uint16_t low)
{
	s_stLaserTcb.stVolThreshold.high = high;
	s_stLaserTcb.stVolThreshold.low = low;

//	BSP_Laser_AdcWDGSet(high, low);
}

/**
 * @brief  APP_Laser_ReadVolThreshold.
 * @note   None.
 * @param  None.
 * @retval *CurThreshold.
 */
ThresholdTypeDef * APP_Laser_ReadVolThreshold(void)
{
	return &s_stLaserTcb.stVolThreshold;
}
