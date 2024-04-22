
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"
#include "Task/Task_FeedBack.h"

/* Define --------------------------------------------------------------------*/

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
SystemParameter_Struct s_stSystemParametser =
{
	.bReady = false,
	.bRun = false,
	.ucErr = 0xFF,
};

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_ReadLaserCount.
 * @note   None.
 * @param  None.
 * @retval ulPulseCNT.
 */
uint32_t APP_ReadLaserCount(void)
{
	return s_stSystemParametser.ulPulseCNT;
}

/**
 * @brief  APP_LaserCountCallback.
 * @note   None.
 * @param  None
 * @retval None.
 */
void APP_LaserCountCallback(void)
{
	if (APP_IsLaserRunning() == false)
		return;
	
	s_stSystemParametser.ulPulseCNT++;
	
	/* send laser cnt */
	APP_SendLaserCount();
}

/**
 * @brief  APP_SetLaserCount.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SetLaserCount(uint32_t count)
{
	s_stSystemParametser.ulPulseCNT = count;
	
	APP_SendLaserCount();
}

/**
 * @brief  APP_SendLaserCount.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SendLaserCount(void)
{
	uint32_t data = APP_ReadLaserCount();
	uint16_t buf[2];
	buf[0] = data >> 16;
	buf[1] = data ;
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_TARGET_LASERCOUNT_MODIFY, 2, buf);
}

/**
 * @brief  APP_ReadTime.
 * @note   None.
 * @param  None
 * @retval stTime.
 */
Time_Struct APP_ReadTime(void)
{
	return s_stSystemParametser.stTime;
}

/**
 * @brief  APP_TimeCallback.
 * @note   None.
 * @param  None
 * @retval None.
 */
void APP_TimeCallback(void)
{
	if (APP_IsLaserRunning() == false)
		return;

	if (++s_stSystemParametser.stTime.ucCnt >= 100)
	{
		s_stSystemParametser.stTime.ucCnt = 0;
				
		if (++s_stSystemParametser.stTime.ucSecond >= 60)
		{
			s_stSystemParametser.stTime.ucSecond = 0;
			if (++s_stSystemParametser.stTime.ucMinute >= 60)
			{
				s_stSystemParametser.stTime.ucMinute = 0;
				if (++s_stSystemParametser.stTime.ucHour >= 24)
					s_stSystemParametser.stTime.ucHour = 0;
			}
		}
		/* send time information */
		APP_SendTime();
	}
}

/**
 * @brief  APP_SetTime.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SetTime(uint8_t hour, uint8_t minute, uint8_t second)
{
	s_stSystemParametser.stTime.ucCnt = 0;
	s_stSystemParametser.stTime.ucHour = hour;
	s_stSystemParametser.stTime.ucMinute = minute;
	s_stSystemParametser.stTime.ucSecond = second;

	/* send time */
	APP_SendTime();
}

/**
 * @brief  APP_SendTime.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SendTime(void)
{
	uint16_t buf[2] = {0};
	Time_Struct time = APP_ReadTime();
	buf[0] = time.ucHour;
	buf[0] <<= 8;
	buf[0] += time.ucMinute; 
	buf[1] = time.ucSecond;
	buf[1] <<= 8;
	
	APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_FEEDBACK, INDEX_TARGET_TIME, 2, buf);
}

/**
 * @brief  Task_LaserRunning.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_LaserRunning(void)
{
	static bool oldflag = false;
	bool flag = false;
	
	if ( APP_KEY_IsPress() && APP_IsSystemReady() ) // || APP_IsFactory()) )
		flag = true;
	
	if (oldflag == flag)
		return;
	
	oldflag = flag;
	
	APP_Laser_OutEnable(flag);
	APP_LaserRunSet(flag);
	
	/* Refresh */
	APP_Protect_RefreshRun();
}

#define ERROR_CODE_HANDPIECE				(uint8_t)0X01
#define ERROR_CODE_WATERTEMPERATURE	(uint8_t)0X02
#define ERROR_CODE_WATERFL0W				(uint8_t)0X03
#define ERROR_CODE_WATERLEVEL				(uint8_t)0X04
#define ERROR_CODE_SAFELOCKER				(uint8_t)0X05

/**
 * @brief  APP_SafeGuard.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SafeGuard(void)
{
	uint8_t errorcode = 0;
#if 0
	/* Handpiece disconnect */
	if ( APP_IsHandpieceError() )
	{
		errorcode |= ERROR_CODE_HANDPIECE;
		goto _stopPump;
	}
#endif

#if 0
	/* Water error */
	if ( APP_IsWaterTemperatureOver() )
	{
		errorcode |= ERROR_CODE_WATERTEMPERATURE;
		goto _stopRun;
	}
	if ( APP_IsWaterFlowErr() ) 
	{
		errorcode |= ERROR_CODE_WATERFL0W;
		goto _stopPump;
	}
	if ( APP_IsWaterLevelErr() )
	{
		errorcode |= ERROR_CODE_WATERLEVEL;
		goto _stopPump;
	}
#endif

#if 0
	/* SafeLocker disconnect */
	if ( APP_IsSafeLockErr() )
	{
		errorcode |= ERROR_CODE_SAFELOCKER;
		goto _stopRun;
	}
#endif
	/*  */
	
	/*  */

#if 0
	/* 27V Abnormal voltage */
	if ( APP_IsVoltageErr() )
		goto _stopRun;
#endif

#if 0
	/* Mos overtemperature */
	if ( APP_IsMosTemperatureOver())
		goto _stopRun;
#endif
	/* not error */
	goto _exit;
	
//_stopPump:
	/*	APP_Pump_Config(false); */

_stopRun:
	APP_SystemReady(false);

	/* Updata Err Code */	
_exit:
	if (s_stSystemParametser.ucErr != errorcode)
	{
		s_stSystemParametser.ucErr = errorcode;
		APP_Send_Data(DEVICE_TYPE, INDEX_TYPE_HEARTBEAT, INDEX_ERROR_CODE, 1, (uint16_t*)(&errorcode));
	}
}

/**
 * @brief  APP_LaserRunSet.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_LaserRunSet(bool bState)
{
	s_stSystemParametser.bRun = bState;
}

/**
 * @brief  APP_IsLaserRunning.
 * @note   None.
 * @param  None.
 * @retval None.
 */
bool APP_IsLaserRunning(void)
{
	return s_stSystemParametser.bRun;
}

/**********************************************************************************************/
/**
 * @brief  APP_SystemReady.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SystemReady(bool bState)
{
	if (bState && APP_KEY_IsPress())	/* Release key */
		return;
	
	if (bState == s_stSystemParametser.bReady)
		return;

	/* enable OR disable Laser power */
	APP_Laser_EnergyReady(bState);
	
	/* cooler config */
	
	/* pump config */
	
	s_stSystemParametser.bReady = bState;
	
	Enable_Feedback(TASK_FB_SYSTEM_READY, 0);
}

/**
 * @brief  APP_IsSystemReady.
 * @note   None.
 * @param  None.
 * @retval None.
 */
bool APP_IsSystemReady(void)
{
	return s_stSystemParametser.bReady;
}
