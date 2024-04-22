
#include "APP/APP_Common.h"

#define LASER_TEST_ID		DAC_1

typedef struct 
{
	__IO bool	bLaserRun;

}FactoryMDL_Struct;

FactoryMDL_Struct s_stFactoryTcb =
{
	.bLaserRun = false,
};

/**
 * @brief  APP_Factory_Init.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_Factory_Init(void)
{
	s_stFactoryTcb.bLaserRun = false;
}

/**
 * @brief  APP_FactoryLaser.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
void APP_FactoryLaser(bool state)
{
	if (state)
	{
//	BSP_DAC_Config(LASER_TEST_ID, 5);
		
		APP_Laser_WriteMode(false);
		
		s_stFactoryTcb.bLaserRun = true;
	}
	else
	{
		
		APP_Laser_WriteMode(true);
		
		s_stFactoryTcb.bLaserRun = false;
	}
}

/**
 * @brief  APP_IsFactory.
 * @note   None.
 * @param  bState.
 * @retval None.
 */
bool APP_IsFactory(void)
{
	return s_stFactoryTcb.bLaserRun;
}
