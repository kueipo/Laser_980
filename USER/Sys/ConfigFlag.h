
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIGFLAG_H
#define __CONFIGFLAG_H

#include "stm32f0xx_hal.h"
#include "BSP/BSP_Common.h"

#ifndef ENTER_APP
#define ENTER_APP		0XA5
#endif

#ifndef UPDATE_APP
#define UPDATE_APP  0XAA
#endif

#if defined(ENABLE_FAL_SUPPORT)
#define cf_UPD_FLAG_ADDR   IAP_FLAG_ADDR_SETOFF //customize
#else
#define cf_UPD_FLAG_ADDR   UPD_FLAG_ADDRESS + IAP_FLAG_ADDR_SETOFF //customize
#define cf_FLASH_Init      FLASH_Init//customize
#define cf_FLASH_Read      FLASH_Read//customize
#define cf_FLASH_Write     FLASH_Write//customize
#define cf_FLASH_Erase     FLASH_Erase//customize
#endif

#define cf_Delay_ms    		 HAL_Delay//customize
#define cf_Restart         HAL_FLASH_OB_Launch//customize

void cf_Config_App_Flag(uint8_t configflag);

#endif  /* __CONFIGFLAG_H */
