#ifndef __BSP_SAFELOCKER_H__
#define __BSP_SAFELOCKER_H__

/* SAFE LOCKER Num */
typedef enum
{
	LOCK_0 = 0x00,
	LOCK_ID_MAX,

} ENUM_LOCK_CHNL_BSP;

/************* LOCK_0 ****************/
#define LOCK_0_PORT SAFELOCKER_0_GPIO_Port
#define LOCK_0_PIN 	SAFELOCKER_0_Pin

void BSP_SafeLock_Init(void);
void BSP_SafeLock_DeInit(void);
uint8_t BSP_SafeLock_State(uint8_t id);

#endif
