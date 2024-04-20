#ifndef __BSP_SAFELOCKER_H__
#define __BSP_SAFELOCKER_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* SAFE LOCKER Num */
typedef enum
{
	LOCKER_0    = 0x00,
	LOCKER_ID_MAX,

}ENUM_LOCK_CHNL_BSP;

/*************KEY 0****************/	   
#define LOCK0_PORT                          SAFELOCKER_0_GPIO_Port
#define LOCK0_PIN                           SAFELOCKER_0_Pin
     
void BSP_SafeLocker_Init(void);
void BSP_SafeLocker_DeInit(void);
uint8_t BSP_SafeLockerValue(uint8_t id);

#ifdef __cplusplus
}
#endif 

#endif
