
/* Includes ------------------------------------------------------------------*/
#include "APP/APP_Common.h"

/* Define --------------------------------------------------------------------*/
#define PROTECT_PULSE_WIDTH_MAX    (LASER_WIDTH * 12) / 10		// uint:ms  +-20%
#define PROTECT_PULSE_OFFSET				1

/* Function prototypes -------------------------------------------------------*/


/* Variables -----------------------------------------------------------------*/
uint16_t const dc24[2] = {0, 0xFFF};

uint16_t const CurrentAdc[][2] = 
{
	{0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, 
	{0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, 
	{0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, 
	{0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, 
	{0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, {0, 0XFFF}, 
};

typedef struct
{
	uint16_t cnt;
	uint16_t Reload;
} WDG_TypeDef;
static WDG_TypeDef wdg;

typedef struct
{
	volatile uint32_t uiVersion;
} Protect_Struct;
static Protect_Struct s_stProtectTcb = {0};

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  Protect Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Protect_Init(void)
{
	APP_Protect_WDG_Init();
}

/**
 * @brief  Protect Task.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Protect_Task(void)
{
	APP_Protect_DC24Range();
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  Send DC24V ADC Range
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Protect_DC24Range(void)
{
	uint16_t val[2];

	val[0] = dc24[0];
	val[1] = dc24[1];
	
	APP_Send_Data(DEV_INDEX_PORTECT, INDEX_TYPE_OPERATE, PROTECT_DC24_ADC, 2, val);
}

/**
 * @brief  APP_Protect_RefreshCurrent
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Protect_RefreshCurrent(void)
{
	uint16_t val[2];
	uint8_t id = APP_Laser_ReadEnergy() - 1;
	
	val[0] = CurrentAdc[id][0];
	val[1] = CurrentAdc[id][1];
	
	APP_Send_Data(DEV_INDEX_PORTECT, INDEX_TYPE_OPERATE, PROTECT_CURRENT_ADC, 2, val);
}

/**
 * @brief  APP_Protect_RefreshPulseWidth
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Protect_RefreshPulseWidth(void)
{
	uint16_t val[2];
	uint8_t frequency = APP_Laser_ReadFrequency();
	bool mode = APP_Laser_ReadPulseMode();
	
	val[0] = 0;
	
	if (mode)
		val[1] = PROTECT_PULSE_WIDTH_MAX / frequency + PROTECT_PULSE_OFFSET;
	else
		val[1] = 0xFFFF;
	
	APP_Send_Data(DEV_INDEX_PORTECT, INDEX_TYPE_OPERATE, PROTECT_PULSEWIDTH, 2, val);
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  APP_Protect_RefreshReady
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Protect_RefreshReady(void)
{
	uint16_t val[1];
	
	val[0] = (uint16_t)APP_IsSystemReady();

	APP_Send_Data(DEV_INDEX_PORTECT, INDEX_TYPE_OPERATE, INDEX_SYSTEM_READY, 1, val);
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  APP_Protect_RefreshRun
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Protect_RefreshRun(void)
{
	uint16_t val[1];
	
	val[0] = (uint16_t)APP_IsLaserRunning();

	APP_Send_Data(DEV_INDEX_PORTECT, INDEX_TYPE_OPERATE, INDEX_SYSTEM_RUNNING, 1, val);
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  APP_Protect_WriteErrorCode
 * @note   None.
 * @param  err.
 * @retval None.
 */
void APP_Protect_WriteErrorCode(uint8_t err)
{
	UNUSED(err);
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  APP_Protect_WDG_Init
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Protect_WDG_Init(void)
{
	wdg.Reload = 1001; // unit:ms, tolerances:1
	wdg.cnt = wdg.Reload;
}

/**
 * @brief  APP_Protect_WDG_Refresh
 * @note   Regular refresh to prevent triggering timeout.
 * @param  None.
 * @retval None.
 */
void APP_Protect_WDG_Refresh(void)
{
	wdg.cnt = wdg.Reload;
}

/**
 * @brief  APP_Protect_WDG_Callback
 * @note   None.
 * @param  period:[unit:ms].
 * @retval None.
 */
void APP_Protect_WDG_Callback(uint16_t period)
{
	if (wdg.cnt > period)
		wdg.cnt -= period;
	else
	/* Trigger timeout */	
		;
}

/**
 * @brief  APP_Protect_WriteVersion
 * @note   None.
 * @param  version.
 * @retval None.
 */
void APP_Protect_WriteVersion(uint32_t version)
{
	s_stProtectTcb.uiVersion = version;
}

/**
 * @brief  APP_Protect_ReadVersion
 * @note   None.
 * @param  None.
 * @retval Verion.
 */
uint32_t APP_Protect_ReadVersion(void)
{
	return s_stProtectTcb.uiVersion;
}
