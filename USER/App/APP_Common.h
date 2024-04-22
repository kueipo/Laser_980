#ifndef __APP_COMMON_H
#define __APP_COMMON_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "global.h"

#include "BSP/BSP_Common.h"

#include "easyflash.h"
#include "inc/fal.h"
#include "ringbuffer.h"
#include "APP/APP_COMMREQ.h"
//#include "APP_Lib.h"
//#include "APP_Config.h"
//#include "APP/APP_HANDPIECE.h"
//#include "APP/APP_KEY.h"
//#include "APP/APP_WATER.h"
//#include "APP/APP_PUMP.h"
//#include "APP/APP_COOLER.h"
#include "APP/APP_Laser.h"
//#include "APP/APP_SafeLocker.h"
#include "APP/APP_Operate.h"
//#include "APP/APP_ACvoltage.h"
//#include "APP/APP_VoltageAdj.h"
#include "APP/APP_LED.h"
//#include "APP/APP_Factory.h"
//#include "APP/APP_Fan.h"
//#include "APP/APP_Mos.h"
#include "APP/app.h"
//#include "APP/APP_DataComm.h"
#include "APP/APP_PageMain.h"
#include "APP/APP_Motor.h"
#include "APP/APP_DC24V.h"

typedef enum
{
	READ = 0U,
	WRITE,
} Data_OPT;

void APP_TimeProc(uint32_t usPeriod);

void APP_Init(void);
bool Send_Data(uint8_t DevID, uint8_t Type, uint8_t Targe, uint8_t Length, uint16_t *pData);

#ifdef __cplusplus
}
#endif

#endif
