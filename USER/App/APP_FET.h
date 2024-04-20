#ifndef __APP_FET_H
#define __APP_FET_H

#ifdef __cplusplus
 extern "C" {
#endif
 
typedef struct 
{	
	volatile uint8_t	ucTemperature;
	volatile uint8_t	ucTemperatureTH;
	volatile bool       bOverTempProtect;
}Fet_Struct;

void APP_Fet_Init(void);
void APP_Fet_Task(void);
uint8_t APP_ReadFetTemperature(void);
void APP_WriteFetTemperatrueTH(uint8_t val);
void APP_WriteFetOverTemperaturePROT(bool state);
bool APP_IsFetTemperatureOver(void);

#ifdef __cplusplus
}
#endif
  
   
#endif
