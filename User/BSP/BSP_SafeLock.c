
/* Includes ------------------------------------------------------------------*/
#include "BSP_Common.h"

/* Configuration table -------------------------------------------------------*/
const BSP_GPIO_CONFIG s_stLockCfg[LOCK_ID_MAX] =
{
	/* Locker_0 ----------------------*/
	{
			.GpioPort = LOCK_0_PORT,
			.GpioPin = LOCK_0_PIN,
			.ActiveLogic = GPIO_PIN_RESET,
	},
};

/* Function prototypes -------------------------------------------------------*/
/**
 * @brief  BSP_SafeLock_Init.
 * @note   None.
 * @param  None.
 * @retval None
 */
void BSP_SafeLock_Init(void)
{
}

/**
 * @brief  BSP_SafeLock_DeInit.
 * @note   None.
 * @param  LockId.
 * @retval None.
 */
void BSP_SafeLock_DeInit(void)
{
	GPIO_TypeDef *GpioPort;
	uint32_t GpioPin;

	for (uint8_t i = 0; i < LOCK_ID_MAX; i++)
	{
		GpioPort = s_stLockCfg[i].GpioPort;
		GpioPin = s_stLockCfg[i].GpioPin;

		HAL_GPIO_DeInit(GpioPort, GpioPin);
	}
}

/**
 * @brief  BSP_SafeLock_State.
 * @note   None.
 * @param  LockId.
 * @retval 0xFF:error.
 *		   	 0:CONN.
 *		   	 1:DISCONN.
 */
uint8_t BSP_SafeLock_State(uint8_t id)
{
	GPIO_TypeDef *GpioPort;
	uint32_t GpioPin;
	GPIO_PinState ActiveLogic;

	if (id >= LOCK_ID_MAX)
		return 0xFF;

	GpioPort = s_stLockCfg[id].GpioPort;
	GpioPin = s_stLockCfg[id].GpioPin;
	ActiveLogic = s_stLockCfg[id].ActiveLogic;

	return (ActiveLogic == HAL_GPIO_ReadPin(GpioPort, GpioPin));
}
