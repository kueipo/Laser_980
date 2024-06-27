#ifndef __BSP_SAFELOCK_H__
#define __BSP_SAFELOCK_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* SAFE LOCKER Num */
typedef enum
{
	LOCK_0    = 0x00,
	LOCK_ID_MAX,

}ENUM_LOCK_CHNL_BSP;

/*************KEY 0****************/	   
#define LOCK0_PORT                          SAFELOCKER_0_GPIO_Port
#define LOCK0_PIN                           SAFELOCKER_0_Pin
     
void BSP_SafeLock_Init(void);
void BSP_SafeLock_DeInit(void);
uint8_t BSP_SafeLock_ReadState(uint8_t id);

#ifdef __cplusplus
}
#endif 

#endif
