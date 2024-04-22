
#ifndef __APP_PUMP_H
#define __APP_PUMP_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum
{
  PUMP_CURRENT   = 0x00,
	PUMP_VOLTAGE,
  PUMP_TASK_MAX,
}ENUM_PUMP_MODLE_BSP;

typedef struct 
{
	uint8_t		ucCurrent;	
	uint16_t	uiVoltage;
	bool		bState;
}PumpModel_Struct;

void APP_Pump_Init(void);
void APP_Pump_Task(void);
void APP_Pump_Config(bool bState);
bool APP_ReadPumpState(void);
uint16_t APP_ReadPumpVoltage(void);
uint8_t APP_ReadPumpCurrent(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_PUMP_H */
