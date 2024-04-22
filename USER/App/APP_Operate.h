
#ifndef __APP_OPERATE_H
#define __APP_OPERATE_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{	volatile uint8_t	ucCnt;
	volatile uint8_t	ucSecond;
	volatile uint8_t	ucMinute;
	volatile uint8_t	ucHour;
}Time_Struct;

void Timer_CLR(void);
uint32_t ReadLaserCount(void);
Time_Struct ReadTime(void);
void APP_LaserCountCallback(void);
void APP_TimeCallback(void);
void APP_LaserRunning(void);
void APP_SafeGuard(void);
void APP_SystemRunSet(bool bState);
bool APP_IsLaserRunning(void);

void APP_SystemReadySet(bool bState);
bool APP_IsSystemRun(void);
void APP_HandlePowerWrite(uint8_t power);
uint8_t APP_HandlePowerRead(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_OPERATE_H */
