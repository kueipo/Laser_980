
/* Includes ------------------------------------------------------------------*/
#include "APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define USING_CC6902SO_10A

/* Function prototypes -------------------------------------------------------*/
static uint8_t PumpCurrent_Detection(void);
static uint16_t PumpVoltage_Detection(void);

/* Variables -----------------------------------------------------------------*/
__IOM PumpModel_Struct s_stPumpTcb;

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_Pump_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Pump_Init(void)
{
	memset((uint8_t*)&s_stPumpTcb, 0, sizeof(s_stPumpTcb));
}

/**
 * @brief  APP_Pump_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */void APP_Pump_Task(void)
{
	static uint8_t index = 0;
	switch (index)
	{
		case PUMP_CURRENT:   
		{
			s_stPumpTcb.ucCurrent = PumpCurrent_Detection();
		}break; 
            
		case PUMP_VOLTAGE:   
		{
			s_stPumpTcb.uiVoltage = PumpVoltage_Detection();
		}break; 
           
		default:
			break;
	}
	if (++index >= PUMP_TASK_MAX)
		index = 0;
}

/**
  * @brief  PumpCurrent_Detection.
  * @note   None.
  * @param  None.
  * @retval CURRENT VAL.
  */
static uint8_t PumpCurrent_Detection(void)
{
	uint32_t PumpCurADC = BSP_ReadADCVal(PUMP_CUR_CHNL);
	
	PumpCurADC = ABS_RETURN( PumpCurADC, 1650 );
	if (PumpCurADC < 20)
		PumpCurADC = 0;
	PumpCurADC *= 15;
#ifdef USING_CC6902SO_10A
	PumpCurADC >>= 1;
#elif defined(USING_CC6902SO_10A)
	PumpCurADC >>= 2;
#elif defined(USING_CC6920SO_40A)
	PumpCurADC <<= 1;
#endif
	PumpCurADC /= 100;
	
	return (uint8_t)PumpCurADC;
}

/**
  * @brief  PumpVoltage_Detection.
  * @note   None.
  * @param  None.
  * @retval PumpVolADC.
  */
static uint16_t PumpVoltage_Detection(void)
{
	uint32_t PumpVolADC = BSP_ReadADCVal(V24_VOL_CHNL);
#if 0	/* Use internal reference voltage */
	PumpVolADC *= 1320;
	PumpVolADC /=  BSP_ReadADCVal(ADC_VREF_CHNL);
#else	/* Use external reference voltage */
	PumpVolADC /= 10;
	PumpVolADC *= 8;
#endif
	return (uint16_t)PumpVolADC;
}

/**
 * @brief  APP_Pump_Config.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_Pump_Config(bool bState)
{
	if (bState)
	{
		if (s_stPumpTcb.bState == false)
		{
			/* delay */
			APP_WaterSpeedSetDelay(2);
			
			BSP_Pump_Operate(PUMP_0, PUMP_ON);
		}
	}
	else
	{
		if (s_stPumpTcb.bState == true)
		{
			BSP_Pump_Operate(PUMP_0, PUMP_OFF);
		}
	}
	
	s_stPumpTcb.bState = bState;
}

/**
 * @brief  APP_ReadPumpState.
 * @note   None.
 * @param  None.
 * @retval state.
 */
bool APP_ReadPumpState(void)
{
	return s_stPumpTcb.bState;
}

/**
 * @brief  APP_ReadPumpVoltage.
 * @note   None.
 * @param  None.
 * @retval uiVoltage.
 */
uint16_t APP_ReadPumpVoltage(void)
{
	return s_stPumpTcb.uiVoltage;
}

/**
 * @brief  APP_ReadPumpCurrent.
 * @note   None.
 * @param  None.
 * @retval ucCurrent.
 */
uint8_t APP_ReadPumpCurrent(void)
{
	return s_stPumpTcb.ucCurrent;
}
