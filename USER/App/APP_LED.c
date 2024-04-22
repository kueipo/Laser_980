
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define	LED_RUN_PERIOD		500
#define LED_INX_FLAG		"LedIdx"

//#define USING_FLASH_INFO
/* Variables -----------------------------------------------------------------*/
typedef struct 
{	
	volatile uint8_t	index;
}Led_Struct;
__IOM Led_Struct s_stLedTcb;

APP_LED_TB s_stAppLedTcb[LED_ID_MAX];

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_LED_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_LED_TimeProc(uint16_t usPeriod)
{
	static uint16_t AppLedTB = 0;
	AppLedTB += usPeriod;
	if (AppLedTB >= LED_RUN_PERIOD)
	{
		/* Set_Task(HCI, HCI_LED); */
		APP_LED_Task();
		AppLedTB -= LED_RUN_PERIOD;
	}
}

/**
 * @brief  APP_LED_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_LED_Init(void)
{
	uint8_t index;

	memset((uint8_t *)&s_stAppLedTcb, 0, sizeof(s_stAppLedTcb));

	for (index = 0; index < LED_ID_MAX; index++)
	{
		s_stAppLedTcb[index].OpMode = APP_LED_OFF;
		s_stAppLedTcb[index].HWState = LED_OFF;
		BSP_Led_Operate(index, s_stAppLedTcb[index].HWState);
	}

#ifdef USING_FLASH_INFO
	/* read index of led from flash */
	uint8_t ledidx[1] = {0};
	if (ef_get_env_blob(LED_INX_FLAG, ledidx, sizeof(ledidx), NULL))
	{
		s_stLedTcb.index = ledidx[0];
	}
	else
	{
		ledidx[0] = APP_LED_BLUE;
		s_stLedTcb.index = ledidx[0];
		ef_set_env_blob(LED_INX_FLAG, ledidx, sizeof(ledidx));
	}
#endif
	APP_LED_Config(LED_BLUE, APP_LED_ON, 0xFFFF, 500, 0);

	/*	APP_LED_Config(APP_LED_GREEN, APP_LED_FLASH, 0xFFFF, 500, 0); */
	/*	APP_LED_Config(APP_LED_BLUE, APP_LED_FLASH, 0xFFFF, 500, 0); */
}

/**
 * @brief  APP_LED_Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_LED_Task(void)
{
	uint8_t HWOpMode;
	uint8_t index;
	for (index = 0; index < LED_ID_MAX; index++)
	{
		HWOpMode = LED_OFF;
		if (APP_LED_FLASH == s_stAppLedTcb[index].OpMode)
		{
			if (s_stAppLedTcb[index].usDelayCnt >= LED_RUN_PERIOD)
			{
				s_stAppLedTcb[index].usDelayCnt -= LED_RUN_PERIOD;
			}
			else
			{
				s_stAppLedTcb[index].usDelayCnt = 0;
			}

			if (s_stAppLedTcb[index].usDelayCnt > 0)
			{
				continue;
			}

			HWOpMode = ((LED_ON == s_stAppLedTcb[index].HWState) ? (LED_OFF) : (LED_ON));
			s_stAppLedTcb[index].usDelayCnt = s_stAppLedTcb[index].usPeriod;

			/*  if ucTime = ~0 */
			if (0xFF == s_stAppLedTcb[index].ucTimes)
			{
				/*	continue; */
			}
			else if (--s_stAppLedTcb[index].ucTimes == 0)
			{
				s_stAppLedTcb[index].OpMode = APP_LED_OFF;
			}
		}
		else
		{
			/* Refresh cnt */
			if (s_stAppLedTcb[index].usTimeCnt >= LED_RUN_PERIOD)
			{
				s_stAppLedTcb[index].usTimeCnt -= LED_RUN_PERIOD;
			}
			else
			{
				s_stAppLedTcb[index].usTimeCnt = 0;
			}

			if ((s_stAppLedTcb[index].usTimeCnt > 0) || (0xFFFF == s_stAppLedTcb[index].usTimeOut))
			{
				continue;
			}
			/* time out, led off */
			HWOpMode = LED_OFF;
		}

		if (HWOpMode == s_stAppLedTcb[index].HWState)
		{
			continue;
		}
		BSP_Led_Operate(index, HWOpMode);
		s_stAppLedTcb[index].HWState = HWOpMode;
	}
}

/**
 * @brief  APP_LED_Config.
 * @note   None.
 * @param  LedId.
 * @param  OpMode.
 * @param  usTimeOut.
 * @param  usPeriod.
 * @param  ucTimes.
 * @retval None.
 */
void APP_LED_Config(uint8_t LedId, uint8_t OpMode, uint16_t usTimeOut, uint16_t usPeriod, uint8_t ucTimes)
{
	uint8_t HWOpMode;

	/* Out of range */
	if (LedId >= LED_ID_MAX)
		return;

	HWOpMode = LED_OFF;
	memset((uint8_t *)&s_stAppLedTcb[LedId], 0, sizeof(APP_LED_TB));

	s_stAppLedTcb[LedId].OpMode = OpMode;

	if (APP_LED_FLASH == OpMode)
	{
		s_stAppLedTcb[LedId].usPeriod = usPeriod;
		s_stAppLedTcb[LedId].usDelayCnt = usPeriod;
		s_stAppLedTcb[LedId].ucTimes = (ucTimes * 2) - 1;
		HWOpMode = LED_TOGGLE;
		s_stAppLedTcb[LedId].HWState = LED_ON;
	}
	else
	{
		s_stAppLedTcb[LedId].usTimeOut = usTimeOut;
		s_stAppLedTcb[LedId].usTimeCnt = usTimeOut;
		if (APP_LED_ON == OpMode)
		{
			HWOpMode = LED_ON;
			s_stAppLedTcb[LedId].HWState = LED_ON;
		}
	}
	BSP_Led_Operate(LedId, HWOpMode);

#ifdef USING_FLASH_INFO
	/* save index of led */
	uint8_t ledidx[1] = {0};
	if (HWOpMode == LED_ON)
	{
		if (LedId != s_stLedTcb.index)
		{
			ledidx[0] = LedId;
			s_stLedTcb.index = ledidx[0];

			/* write flash */
			ef_set_env_blob(LED_INX_FLAG, ledidx, sizeof(ledidx));
		}
	}
#endif
}
