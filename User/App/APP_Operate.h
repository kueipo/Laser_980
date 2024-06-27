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
	volatile uint8_t ucErrCode;
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
void APP_Operate_Task(void);
void APP_Operate_SafeGuardTask(void);
uint8_t APP_Operate_ReadErrCode(void);
void APP_Operate_WriteLaserRunState(bool bState);
bool APP_Operate_IsLaserRunning(void);

void APP_Operate_WreiteSystemReady(bool bState);
bool APP_Operate_IsSystemReady(void);

#ifdef __cplusplus
}
#endif

#endif
