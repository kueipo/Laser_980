/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __APP_COMMON_H
#define __APP_COMMON_H

/* Exported types ------------------------------------------------------------*/
typedef enum {
	READ = 0U,
	WRITE,
} Data_OPT;

/* Includes ------------------------------------------------------------------*/
#include "BSP/BSP_Common.h"

//#include "APP_Lib.h"
//#include "APP_Config.h"

#include "CRC16.h"

#include "APP/APP_COMMREQ.h"
#include "APP/APP_HANDPIECE.h"
#include "APP/APP_KEY.h"
//#include "APP/APP_WATER.h"
//#include "APP/APP_PUMP.h"
//#include "APP/APP_COOLER.h"
#include "APP/APP_Laser.h"
#include "APP/APP_SafeLocker.h"
#include "APP/APP_Operate.h"
#include "APP/APP_ACvoltage.h"
#include "APP/APP_VoltageAdj.h"
#include "APP/APP_LED.h"
#include "APP/APP_Factory.h"
#include "APP/APP_Fan.h"
#include "APP/APP_MOS.h"
#include "APP/APP_VoltageDetection.h"
#include "APP/APP_Protect.h"
#include "APP/APP.h"
#include "APP/APP_Buzzer.h"
#include "IAP/INC/iap.h"

#include "Task/Task_PolityHigh.h"

/* External functions --------------------------------------------------------*/
void APP_TimeProc(uint8_t ucPeriod);
void APP_Init(void);
bool APP_Send_Data(uint8_t DevID, uint8_t Type, uint8_t Targe, uint8_t Length, uint16_t *pData);

#endif /* __APP_COMMON_H */
