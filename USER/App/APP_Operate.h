#ifndef __APP_OPERATE_H
#define __APP_OPERATE_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct 
{	volatile uint8_t ucCnt;
	volatile uint8_t ucSecond;	
	volatile uint8_t ucMinute;
	volatile uint8_t ucHour;
}Time_Struct;

typedef struct 
{
	volatile uint32_t ulPulseCNT;
	volatile uint8_t ucErr;
	volatile bool bReady;
	volatile bool bRun;
	Time_Struct stTime;
}SystemParameter_Struct;

uint32_t APP_ReadLaserCount(void);
Time_Struct APP_ReadTime(void);
void APP_SetLaserCount(uint32_t count);
void APP_LaserCountCallback(void);
void APP_SendLaserCount(void);
void APP_SetTime(uint8_t hour, uint8_t minute, uint8_t second);
void APP_TimeCallback(void);
void APP_SendTime(void);
void APP_LaserRunning(void);
void APP_SafeGuard(void);
void APP_LaserRunSet(bool bState);
bool APP_IsLaserRunning(void);

void APP_SystemReady(bool bState);
bool APP_IsSystemReady(void);
#ifdef __cplusplus
}
#endif

#endif
