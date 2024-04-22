#ifndef __APP_WATER_H
#define __APP_WATER_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef enum
{
    WATER_LEVEL    = 0x00,
	WATER_TEMPERATURE,
	WATER_SPEED,
    WATER_MAX,
}ENUM_WATER_TASK;

typedef enum
{
    WATER_HIGH  = 0,
    WATER_LOW,
    WATER_ERROE,
} ENUM_WATERLEVEL_STATUS;

typedef struct 
{
	uint8_t		ucLevel;	
	uint8_t		ucTemperature;
	uint8_t		ucTemperatureTH;
	uint16_t	uiSpeed;
	uint8_t		ucSpeedDelay;
	bool        bOverTempProtect;
	bool		bFlowProtect;
	bool		bLevelProtect;

}WaterModel_Struct;

void APP_Water_Init(void);
void APP_Water_Task(void);
uint8_t APP_ReadWaterLevel(void);
uint8_t APP_ReadWaterTemperature(void);
uint8_t APP_ReadWaterFlow(void);
void APP_WriteWaterTemperatrueTH(uint8_t val);
void APP_WriteWaterOverTemperaturePROT(bool bState);
void APP_WriteWaterFlowPROT(bool bState);
void APP_WriteWaterLevelPROT(bool bState);
bool APP_IsWaterTemperatureOver(void);
bool APP_IsWaterFlowErr(void);
bool APP_IsWaterLevelErr(void);
void APP_WaterSpeedInit(uint8_t ucDelay);
#ifdef __cplusplus
}
#endif
  
   
#endif
