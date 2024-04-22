
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define ENABLE_TIME_FUNC 0
#define ENABLE_PULSER_FUNC 0
/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/
typedef struct 
{
#if ENABLE_PULSER_FUNC
	volatile uint32_t	ulPulseCNT;
#endif /* ENABLE_PULSER_FUNC */
	volatile uint8_t	ucErr;
	volatile uint8_t	ucPower;
	volatile bool		bRun;
#if ENABLE_TIME_FUNC
	Time_Struct 		stTime;
#endif /* ENABLE_TIME_FUNC */
}SystemParameter_Struct;

__IOM SystemParameter_Struct s_stSystemParametser = {
	.ucErr = 0xFF,
	.ucPower = 1,
	.bRun = false,
};

/* Function prototypes -------------------------------------------------------*/

/**
 * @brief  Timer_CLR.
 * @note   None.
 * @param  None.
 * @retval None.
 */
#if ENABLE_TIME_FUNC
void Timer_CLR(void)
{
	s_stSystemParametser.stTime.ucCnt = 0;
	s_stSystemParametser.stTime.ucHour = 0;
	s_stSystemParametser.stTime.ucMinute = 0;
	s_stSystemParametser.stTime.ucSecond = 0;

	/* send time */
	Enable_PHTask(SENDTIME);

	s_stSystemParametser.ulPulseCNT = 0;
	/* send laser cnt */
	Enable_PHTask(SENDLASERCOUNT);
}
#else
#define Timer_CLR()
#endif /* ENABLE_TIME_FUNC */
/**
 * @brief  ReadTime.
 * @note   None.
 * @param  None
 * @retval stTime.
 */
#if ENABLE_TIME_FUNC
Time_Struct ReadTime(void)
{
	return s_stSystemParametser.stTime;
}
#else 
#define ReadTime()
#endif /* ENABLE_TIME_FUNC */
/**
 * @brief  APP_TimeCallback.
 * @note   None.
 * @param  None
 * @retval None.
 */
#if ENABLE_TIME_FUNC
void APP_TimeCallback(void)
{
	if (APP_IsSystemRun() == false)
		return;

	if (++s_stSystemParametser.stTime.ucCnt >= 100)
	{
		s_stSystemParametser.stTime.ucCnt = 0;

		/* send time information */
		Enable_PHTask(SENDTIME);

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
	}
}
#else
#define APP_TimeCallback()
#endif /*  */

/**
 * @brief  APP_SystemRunSet.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_SystemRunSet(bool bState)
{
	/* Unchanged */
	if (bState == s_stSystemParametser.bRun)
		return;

	s_stSystemParametser.bRun = bState;

}

/**
 * @brief  APP_IsSystemRun.
 * @note   None.
 * @param  None.
 * @retval None.
 */
bool APP_IsSystemRun(void)
{
	return s_stSystemParametser.bRun;
}
