
#ifndef __APP_DC24V_H
#define __APP_DC24V_H

#ifdef __cplusplus
 extern "C" {
#endif

void APP_DC24V_Init(void);
void APP_DC24V_Task(void);
void APP_DC24V_WriteADC(uint16_t th_l, uint16_t th_h);
uint16_t* APP_DC24V_ReadADC(void);
bool APP_IsVoltageErr(void);

#ifdef __cplusplus
}
#endif
  
#endif
