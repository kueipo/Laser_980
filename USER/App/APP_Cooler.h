#ifndef __APP_COOLER_H
#define __APP_COOLER_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum
{
    COOLER_CURRENT   = 0x00,
	COOLER_VOLTAGE,
	
    COOLER_TASK_MAX,
}ENUM_COOLER_MODLE;

typedef struct 
{	
	uint8_t		ucCurrent;	
	uint16_t	uiVoltage;
	uint8_t		ucPower;
	bool		bRun;
}CoolerModel_Struct;

void APP_Cooler_Init(void);
void APP_Cooler_Task(void);
bool APP_CoolerConfig(uint8_t ucCoolerId, uint8_t ucPowerOut);
bool APP_ReadCoolerState(uint8_t ucCoolerId);
uint16_t APP_ReadCoolerVoltage(uint8_t ucCoolerId);
uint8_t APP_ReadCoolerCurrent(uint8_t ucCoolerId);
uint8_t APP_ReadCoolerPower(uint8_t ucCoolerId);

#ifdef __cplusplus
}
#endif

#endif

