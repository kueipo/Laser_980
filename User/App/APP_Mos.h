#ifndef __APP_MOS_H
#define __APP_MOS_H

#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{
	volatile uint8_t ucTemperature;
	volatile uint8_t ucTemperatureTH;
	volatile bool bOverTempProtect;
} Mos_Struct;

void APP_Mos_Init(void);
void APP_Mos_Task(void);
uint8_t APP_Mos_ReadTemperature(void);
void APP_Mos_WriteTemperatrueTH(uint8_t val);
uint8_t APP_Water_ReadTemperatrueTH(void);
void APP_Mos_WriteOverTemperaturePROT(bool state);
bool APP_Mos_ReadOverTemperaturePROT(void);
bool APP_Mos_IsTemperatureOver(void);

#ifdef __cplusplus
 }
#endif

#endif
