
#ifndef __APP_BUZZER_H
#define __APP_BUZZER_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct 
{
	volatile uint8_t ucTime;
	volatile bool	bState;
	volatile bool	bEnable;
	const char*	pEnv;
}Buzzer_Struct;

void APP_Buzzer_Init(void);
void APP_Buzzer_Task(void);
void APP_Buzzer_Config(uint8_t id, bool bState);
void APP_Buzzer_Long(uint8_t id, bool bState);
void APP_Buzzer_SetEnableBit(uint8_t id, bool bState);
bool APP_Buzzer_GetEnableBit(uint8_t id);

#ifdef __cplusplus
}
#endif
  
   
#endif

