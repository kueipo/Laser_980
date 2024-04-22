#ifndef __APP_MOS_H
#define __APP_MOS_H

#ifdef __cplusplus
 extern "C" {
#endif
 
typedef struct 
{	
	volatile uint8_t	ucTemperature;
	volatile uint8_t	ucTemperatureTH;
	volatile bool       bOverTempProtect;
}Mos_Struct;

void APP_Mos_Init(void);
void APP_Mos_Task(void);
uint8_t APP_ReadMosTemperature(void);
void APP_WriteMosTemperatrueTH(uint8_t val);
void APP_WriteMosOverTemperaturePROT(bool state);
bool APP_IsMosTemperatureOver(void);

#ifdef __cplusplus
}
#endif
  
   
#endif
