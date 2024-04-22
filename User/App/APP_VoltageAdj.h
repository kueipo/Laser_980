#ifndef __APP_VOLTAGEADJ_H
#define __APP_VOLTAGEADJ_H

#ifdef __cplusplus
extern "C"
{
#endif

void APP_Voltage_Init(void);
void APP_VoltageAdj(uint8_t vol);
void APP_VoltageConfig(uint8_t num);
void APP_Voltage_Task(void);
bool APP_IsVoltageErr(void);
uint8_t APP_Voltage_OptBarNum(Data_OPT opt, uint8_t num);

#ifdef __cplusplus
}
#endif

#endif
