
/* Includes ------------------------------------------------------------------*/
#include "APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define	LED_RUN_PERIOD	500
#define LED_INX_FLAG		"LedIdx"
#define LED_COLOR_FLAG	"color"

/* Variables -----------------------------------------------------------------*/
typedef struct 
{	
	volatile uint8_t state[LED_ID_MAX];
	volatile uint8_t color[3];
}Led_Struct;
__IOM Led_Struct s_stLedTcb;

APP_LED_TB s_stAppLedTcb[LED_ID_MAX];

/* prototypes ----------------------------------------------------------------*/
static void Save_Parameters(uint8_t LedId, uint8_t OpMode);
static void Get_Parameters(void);
static void Save_Color(uint8_t red, uint8_t green, uint8_t blue);
static void Get_Color(void);

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
		/*  Set_Task(HCI, HCI_LED); */
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

	Get_Color();
	Get_Parameters();
	
	for (index = 0; index < LED_ID_MAX; index++)
	{
		s_stAppLedTcb[index].OpMode = s_stLedTcb.state[index];
		APP_LED_Config(index, s_stAppLedTcb[index].OpMode, 0xFFFF, 500, 0);
	}

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

	Save_Parameters(LedId, OpMode);
}

/**
 * @brief  APP_LED_AllConfig.
 * @note   None.
 * @param  OpMode.
 * @param  usTimeOut.
 * @param  usPeriod.
 * @param  ucTimes.
 * @retval None.
 */
void APP_LED_AllConfig(uint8_t OpMode, uint16_t usTimeOut, uint16_t usPeriod, uint8_t ucTimes)
{
	for (uint8_t index = 0; index < LED_ID_MAX; index++)
		APP_LED_Config(index, OpMode, usTimeOut, usPeriod, ucTimes);
}

/**
 * @brief  APP_LED_ConfigColor.
 * @note   None.
 * @param  red.
 * @param  green.
 * @param  blue.
 * @retval None.
 */
void APP_LED_ConfigColor(uint8_t red, uint8_t green, uint8_t blue)
{
	BSP_Led_Config(APP_LED_RED, red);
	BSP_Led_Config(APP_LED_GREEN, green);
	BSP_Led_Config(APP_LED_BLUE, blue);
	Save_Color(red, green, blue);
}

/* -------------------------------------------------------------------------------------- */
static void Save_Parameters(uint8_t LedId, uint8_t OpMode)
{
	/* save index of led to flash*/
	uint8_t val[LED_ID_MAX] = {0};

	if (OpMode == APP_LED_FLASH)
		return;

	if (OpMode != s_stLedTcb.state[LedId])
	{
		s_stLedTcb.state[LedId] = OpMode;

		memcpy((uint8_t *)&(val), (uint8_t *)&(s_stLedTcb.state), LED_ID_MAX);

		ef_set_env_blob(LED_INX_FLAG, (uint8_t *)&(val), LED_ID_MAX);
	}
}

static void Get_Parameters(void)
{
	/* read index of led from flash */
	uint8_t val[LED_ID_MAX] = {0};
	size_t size;

	if (ef_get_env_blob(LED_INX_FLAG, &val, LED_ID_MAX, &size))
	{
		if (LED_ID_MAX == size)
		{
			memcpy((uint8_t *)&(s_stLedTcb.state), val, size);
			return;
		}
	}

	s_stLedTcb.state[0] = LED_ON;
	memcpy((uint8_t *)&(val), (uint8_t *)&(s_stLedTcb.state), LED_ID_MAX);
	ef_set_env_blob(LED_INX_FLAG, (uint8_t *)&(val), LED_ID_MAX);
}

static void Save_Color(uint8_t red, uint8_t green, uint8_t blue)
{
	if (s_stLedTcb.color[0] == red && s_stLedTcb.color[1] == green && s_stLedTcb.color[2] == blue)
		return;
	
	s_stLedTcb.color[0] = red;
	s_stLedTcb.color[1] = green;
	s_stLedTcb.color[2] = blue;
	ef_set_env_blob(LED_COLOR_FLAG, (uint8_t *)&(s_stLedTcb.color), 3);
}

static void Get_Color(void)
{
	uint8_t val[3];
	size_t size;
	
	if (ef_get_env_blob(LED_COLOR_FLAG, &val, 3, &size) == 3)
	{
		;
	}
	else
	{
		val[0] = 0xff;
		val[1] = 0xff;
		val[2] = 0xff;
		ef_set_env_blob(LED_COLOR_FLAG, (uint8_t *)&(val), 3);
	}
	APP_LED_ConfigColor(val[0], val[1], val[2]);
}
