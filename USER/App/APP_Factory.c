
#include "APP/APP_Common.h"

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
void APP_FactoryLaser(bool bState)
{
  if (bState)
  {
    BSP_Power_Config(5);
    s_stFactoryTcb.bLaserRun = true;

    BSP_Frenquency_Config(10000, 10000 + 1);
  }
  else
  {
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
