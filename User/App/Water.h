#ifndef __WATER_H
#define __WATER_H

#include "DEV_Config.h"

void Water_Init(void);
void Water_Run(void);
void Water_PumpControl(bool state);
void Water_TemperatureWrite(uint8_t val);
uint8_t Water_TemperatureRead(void);
void Water_SpeedWrite(uint16_t val);
uint16_t Water_SpeedRead(void);
void Water_LevelWrite(uint8_t val);
uint8_t Water_LevelRead(void);

#endif  /* __FAN_H */
