
#ifndef __APP_PROTECT_H
#define __APP_PROTECT_H

void APP_Protect_Init(void);
void APP_Protect_Task(void);
void APP_Protect_SendSpeedRange(uint8_t level0, uint8_t level1);
void APP_Protect_DC24Range(void);
void APP_Protect_RefreshCurrent(void);
void APP_Protect_RefreshPulseWidth(void);
void APP_Protect_RefreshReady(void);
void APP_Protect_RefreshRun(void);
void APP_Protect_WriteErrorCode(uint8_t err);
void APP_Protect_WDG_Init(void);
void APP_Protect_WDG_Refresh(void);
void APP_Protect_WDG_Callback(uint16_t period);
void APP_Protect_WriteVersion(uint32_t version);
uint32_t APP_Protect_ReadVersion(void);

#endif /* __APP_PROTECT_H */
