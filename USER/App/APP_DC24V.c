
/* Includes ------------------------------------------------------------------*/
#include "APP_Common.h"

/* Define --------------------------------------------------------------------*/
//#define BAR_FLAG	"barNum"

/* Function prototypes -------------------------------------------------------*/

/* Variables -----------------------------------------------------------------*/

/*
 * 1300 + 4 * Vin = Vout
 * Vin = (Vout - 1300) / 4
 * Vout = (3300 / 4096) * AD
 * Vin = [(3300 / 4096) * AD - 1300] / 4
 * AD = (Vin * 4 + 1300) * 4096 / 3300
 * Vin = VDD / 83
 * AD = [(VDD / 83) * 4 + 1300] * 4096 / 3300
 * DC23C: AD = 1751
 * DC24V: AD = 1757
 * DC25V: AD = 1763
 */

typedef struct 
{
	volatile uint16_t	usTH_L;
	volatile uint16_t	usTH_H;
	volatile uint16_t	usAdc;
	volatile bool		bError;
}DC24V_Struct;

DC24V_Struct s_stDC24VTcb;

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  APP_DC24V_Init.
 * @note   None.
 * @param  vol.
 * @retval	None.
 */
void APP_DC24V_Init(void)
{
	s_stDC24VTcb.bError = false;
	s_stDC24VTcb.usTH_L = 0;
	s_stDC24VTcb.usTH_H = 0xFFFF;

	/* read number of the val from flash */
	//	uint8_t barnum[2] = {0};
	//	uint8_t tmp;

	//	if (ef_get_env_blob(BAR_FLAG, barnum, sizeof(barnum), NULL))
	//	{
	//		s_stDC24VTcb.ucBarNum = barnum[0];
	//	}
	//	else
	//	{
	//		tmp = 14;
	//		s_stDC24VTcb.ucBarNum = tmp;
	//		ef_set_env_blob(BAR_FLAG, &tmp, sizeof(tmp));
	//	}
}

/**
 * @brief  APP_DC24V_Task.
 * @note   None.
 * @param  None.
 * @retval	None.
 */
void APP_DC24V_Task(void)
{
	//	static bool delayflag = false;
	uint16_t threshold_H = s_stDC24VTcb.usTH_H;
	uint16_t threshold_L = s_stDC24VTcb.usTH_L;
	uint16_t volADC = BSP_ReadADCVal(DC24_VOL_CHNL);

	/* Is Running, return */
	//	if (APP_IsLaserRunning())
	//	{
	//		delayflag = false;
	//		goto __exit;
	//	}

	/* Is delay */
	//	if (delayflag == false)
	//	{
	//		delayflag = true;
	//		goto __exit;
	//	}

	s_stDC24VTcb.bError = true;

	s_stDC24VTcb.usAdc += volADC;
	s_stDC24VTcb.usAdc >>= 1;

	/* Voltage Over or Low */
	if (s_stDC24VTcb.usAdc > threshold_H || s_stDC24VTcb.usAdc < threshold_L)
	{
		;
	}
	/* Voltage OK */
	else
	{
		s_stDC24VTcb.bError = false;
	}
}

/**
 * @brief  APP_DC24V_WriteADC.
 * @note   None.
 * @param  th_h.
 * @param  th_l.
 * @retval	None.
 */
void APP_DC24V_WriteADC(uint16_t th_l, uint16_t th_h)
{
	s_stDC24VTcb.usTH_L = th_l;
	s_stDC24VTcb.usTH_H = th_h;
}

/**
 * @brief  APP_DC24V_ReadADC.
 * @note   None.
 * @param  Noe.
 * @retval	None.
 */
uint16_t *APP_DC24V_ReadADC(void)
{
	return (uint16_t *)&s_stDC24VTcb.usTH_L;
}

/**
 * @brief  APP_IsVoltageErr.
 * @note   Voltage error.
 * @param  None.
 * @retval error.
 */
bool APP_IsVoltageErr(void)
{
	return s_stDC24VTcb.bError;
}
