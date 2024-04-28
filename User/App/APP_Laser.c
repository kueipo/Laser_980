
/* Includes ------------------------------------------------------------------*/
#include "APP_Common.h"
#include "DEV_Config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define PULSE_WIDTH_MAX		LASER_WIDTH * 10
#define PULSE_LEVEL_MAX		10U
#define PULSE_LEVEL_MIN		1U
#define LASER_FR_MAX			5U
#define LASER_FR_MIM			1U
#define LASER_ENERGY_MAX	30U
#define INDICATOR_ENERGY_MAX	10U

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint16_t ENERGY[LASER_ENERGY_MAX] = 
{  
	  250,  365,  500,  620,  740,  850,  970, 1090, 1230, 1340, 
	 1440, 1540, 1660, 1780, 1880, 2000, 2120, 2240, 2360, 2480,
	 2600, 2720, 2840, 2960, 3080, 3200, 3320, 3440, 3560, 3680
};

typedef enum
{
	LASER_980	= 0x00,
	LASER_630,
	LASER_ID_MAX,
}ENUM_LASER_ID_TCB;

typedef struct 
{	
	volatile uint8_t ucFrenquency;
	volatile uint8_t ucPulse;
	volatile uint16_t usPulseWidth;
	volatile uint8_t ucEnergy;
	volatile uint8_t ucChannel;
	volatile bool bReady;
	volatile bool bRun;
	volatile bool bMode;
}Laser_Struct;
Laser_Struct s_stLaserTcb[LASER_ID_MAX] =
{
	{
		.ucFrenquency = LASER_FR_MIM,
		.ucPulse = PULSE_LEVEL_MIN,
		.usPulseWidth = 1,
		.ucEnergy = 1,
		.ucChannel = DAC_2,
		.bReady = true,
		.bRun = true,
		.bMode = true,
	},
	{
		.ucEnergy = 0,
		.ucChannel = DAC_1,
		.bReady = true,
		.bRun = true,
	},
};

/* Private function prototypes -----------------------------------------------*/
static void APP_LaserRefresh(void);
static void APP_LaserRefreshMedical(void);

/* Exported functions --------------------------------------------------------*/
/**
 * @brief  FanPowerVal.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void APP_Laser_Init(void)
{
	APP_Laser_WriteMode(false);
	APP_Laser_EnergyReady(false);
	APP_Laser_OutEnable(false);
	
	APP_Laser_IndicatorWriteEnergy(0);
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  APP_Laser_WriteFrequency.
 * @note   None.
 * @param  Frenquency.
 * @retval None.
 */
void APP_Laser_WriteFrequency(uint8_t fenquency)
{
	uint8_t index = LASER_980;
	
	if ((fenquency < LASER_FR_MIM) || (fenquency > LASER_FR_MAX))
		return;
	
	if (s_stLaserTcb[index].ucFrenquency == fenquency)
		return;
	
	s_stLaserTcb[index].ucFrenquency = fenquency;
	APP_LaserRefresh();
}

/**
 * @brief  APP_Laser_ReadFrequency.
 * @note   None.
 * @param  None.
 * @retval Frenquency.
 */
uint8_t APP_Laser_ReadFrequency(void)
{
	uint8_t index = LASER_980;
	
	return s_stLaserTcb[index].ucFrenquency;
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  APP_Laser_WritePulse.
 * @note   None.
 * @param  ucLevel.
 * @retval bool.
 */
bool APP_Laser_WritePulse(uint8_t level)
{
	uint8_t index = LASER_980;
	
	if (level < PULSE_LEVEL_MIN || level > PULSE_LEVEL_MAX)
		return false;

	if (s_stLaserTcb[index].ucPulse == level)
		return true;
	
	s_stLaserTcb[index].ucPulse = level;
	APP_LaserRefresh();

	return true;
}

/**
 * @brief  APP_LaserReadPulse.
 * @note   None.
 * @param  None.
 * @retval Pulse.
 */
uint8_t APP_LaserReadPulse(void)
{
	uint8_t index = LASER_980;
	
	return s_stLaserTcb[index].ucPulse;
}

/* ---------------------------------------------------------------------------*/
/**
 * @brief  APP_Laser_WriteEnergy.
 * @note   None.
 * @param  ucEnergy.
 * @retval bool.
 */
bool APP_Laser_WriteEnergy(uint8_t energy)
{
	uint16_t val;
	uint8_t index = LASER_980;
	uint8_t channel = s_stLaserTcb[index].ucChannel;
	
	if ( energy > LASER_ENERGY_MAX || energy == 0)
		return false;
		
	s_stLaserTcb[index].ucEnergy = energy;
//	val =  (energy - 1) * 365 + 800;
//	val =  (energy - 1) * 160 + 500;
	val = ENERGY[energy - 1];
		
	/* if working, refresh */
	if (s_stLaserTcb[index].bReady == true)
		BSP_DAC_Config(channel, val);
	
	/* refresh laser current (protect) */
	APP_Protect_RefreshCurrent();
	
	return true;
}

/**
 * @brief  APP_Laser_ReadEnergy.
 * @note   None.
 * @param  None.
 * @retval Energy.
 */
uint8_t APP_Laser_ReadEnergy(void)
{
	uint8_t index = LASER_980;
	
	return s_stLaserTcb[index].ucEnergy;
}
/* ---------------------------------------------------------------------------*/
/**
 * @brief  APP_Laser_WriteMode.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_Laser_WriteMode(bool state)
{
	uint8_t index = LASER_980;
	
	/* SW */
	if (state)
		s_stLaserTcb[index].bMode = true;
	/* Pulse */
	else
		s_stLaserTcb[index].bMode = false;

	APP_LaserRefresh();
}

/**
 * @brief  APP_Laser_ReadPulseMode.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
bool APP_Laser_ReadPulseMode(void)
{
	uint8_t index = LASER_980;
	return s_stLaserTcb[index].bMode;
}

/**
 * @brief  APP_Laser_EnergyReady.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_Laser_EnergyReady(bool state)
{
	uint8_t index = LASER_980;
	uint8_t channel = s_stLaserTcb[index].ucChannel;
	
	if (s_stLaserTcb[index].bReady == state)
		return;
	
	s_stLaserTcb[index].bReady = state;
	
	if (state)
	{
		/* Refresh Energy */
		APP_Laser_WriteEnergy(s_stLaserTcb[index].ucEnergy);

		/* Refresh frequency */
//		APP_Laser_WritePulse(s_stLaserTcb[index].ucPulse);
//		APP_Laser_WriteFrequency(s_stLaserTcb[index].ucFrenquency);
		
//		APP_LaserRefresh();
		APP_LaserRefreshMedical();
	}
	else
		BSP_DAC_Config(channel, 0);
}

/**
 * @brief  APP_Laser_OutEnable.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_Laser_OutEnable(bool state)
{
	uint8_t index = LASER_980;
	
	if (state == s_stLaserTcb[index].bRun)
		return;
		
	s_stLaserTcb[index].bRun = state;

	if (state)
	{
		BSP_Frenquency_Enable();
		
		if (APP_Laser_ReadPulseMode())
			APP_Buzzer_Long(BUZZER_0, true);
	}
	else
	{
		BSP_Frenquency_Disable();
		
		if (APP_Laser_ReadPulseMode())
			APP_Buzzer_Long(BUZZER_0, false);
	}
}

/**
 * @brief  APP_LaserRefresh.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void APP_LaserRefresh(void)
{
	uint16_t Period;
	uint16_t Pulse;

	uint8_t index = LASER_980;

	BSP_Frenquency_Disable();
	s_stLaserTcb[index].bRun = false;

	if (s_stLaserTcb[index].bMode)
	{
		Period = 10000;
		Pulse = Period;
	}
	else
	{
		Period = 10000 / s_stLaserTcb[index].ucFrenquency;
		Pulse = PULSE_WIDTH_MAX * s_stLaserTcb[index].ucPulse;
		Pulse = Pulse / PULSE_LEVEL_MAX;
		Pulse = Pulse / s_stLaserTcb[index].ucFrenquency;
	}
		
	BSP_Frenquency_Config(Period, Pulse + 300);
	
	/* Refresh pulse width (protect) */
	APP_Protect_RefreshPulseWidth();
}

/* Medical Begin ------------------------------------------------------------ */
/**
 * @brief  APP_LaserRefreshMedical.
 * @note   None.
 * @param  None.
 * @retval None.
 */
static void APP_LaserRefreshMedical(void)
{
	uint16_t Period;
	uint16_t Pulse;

	uint8_t index = LASER_980;

	if (s_stLaserTcb[index].bReady == false)
		return;
	
	/* Disable output */
	BSP_Frenquency_Disable();
	s_stLaserTcb[index].bRun = false;

	/* Refresh pulse width (main) */
	if (s_stLaserTcb[index].bMode)
	{
		Period = 10000;
		Pulse = Period;
	}
	else
	{
		Period = 10000 / s_stLaserTcb[index].ucFrenquency;
		Pulse = s_stLaserTcb[index].usPulseWidth * 10;
	}

	BSP_Frenquency_Config(Period, Pulse + 20);
	
	/* Refresh pulse width (protect) */
	APP_Protect_RefreshPulseWidth();
}

/**
 * @brief  APP_Laser_WritePulseMedical.
 * @note   None.
 * @param  ucLevel.
 * @retval bool.
 */
bool APP_Laser_WritePulseMedical(uint8_t level)
{
	uint8_t index = LASER_980;
	uint16_t Pulse;
	uint8_t frenquency = s_stLaserTcb[index].ucFrenquency;
	
	if (level < PULSE_LEVEL_MIN || level > PULSE_LEVEL_MAX)
		return false;

	if (s_stLaserTcb[index].ucPulse == level)
		return true;
	
	s_stLaserTcb[index].ucPulse = level;
	
#if 0 /* Divide pulse width equally by frequency */
	Pulse = PULSE_WIDTH_MAX * level;
	Pulse = Pulse / PULSE_LEVEL_MAX;
	Pulse = Pulse / frenquency;	
#else
	Pulse = PULSE_WIDTH_MAX * level;
	Pulse = Pulse / PULSE_LEVEL_MAX;
	if (Pulse < (10000 / frenquency))
#endif
		s_stLaserTcb[index].usPulseWidth = Pulse;
	
	APP_LaserRefreshMedical();

	return true;
}

/**
 * @brief  APP_Laser_WritePulseWidth.
 * @note   None.
 * @param  ms.
 * @retval bool.
 */
bool APP_Laser_WritePulseWidth(uint16_t pulsewidth)
{
	uint8_t index = LASER_980;
	
	if (pulsewidth < 1 || pulsewidth > (PULSE_WIDTH_MAX / 10))
		return false;

	if (s_stLaserTcb[index].usPulseWidth == pulsewidth)
		return true;
	
	s_stLaserTcb[index].usPulseWidth = pulsewidth;
	APP_LaserRefreshMedical();

	return true;
}

/**
 * @brief  APP_LaserReadPulseWidth.
 * @note   None.
 * @param  None.
 * @retval Pulse.
 */
uint16_t APP_LaserReadPulseWidth(void)
{
	uint8_t index = LASER_980;
	
	return s_stLaserTcb[index].usPulseWidth;
}

/* Medical End -------------------------------------------------------------- */

/* 630nm -------------------------------------------------------------------- */
#define LEVEL_630_MAX	5
uint16_t const LaserIndicator[LEVEL_630_MAX] = {
	0, 1200, 1474, 1802, 2129};
/**
 * @brief  APP_Laser_IndicatorWriteEnergy.
 * @note   None.
 * @param  ucEnergy.
 * @retval bool.
 */
bool APP_Laser_IndicatorWriteEnergy(uint8_t energy)
{
	uint16_t val;
	uint8_t index = LASER_630;
	uint8_t channel = s_stLaserTcb[index].ucChannel;
	
	if (energy >= LEVEL_630_MAX)
		return false;
	
	s_stLaserTcb[index].ucEnergy = energy;
	val = LaserIndicator[energy];
	
	BSP_DAC_Config(channel, val);
		
	return true;
}

/**
 * @brief  APP_Laser_IndicatorReadEnergy.
 * @note   None.
 * @param  None.
 * @retval Energy.
 */
uint8_t APP_Laser_IndicatorReadEnergy(void)
{
	uint8_t index = LASER_630;
	
	return s_stLaserTcb[index].ucEnergy;
}
