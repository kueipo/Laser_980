#ifndef __APP_LASER_H
#define __APP_LASER_H

void APP_Laser_Init(void);
void APP_Laser_WriteFrequency(uint8_t fenquency);
uint8_t APP_Laser_ReadFrequency(void);
bool APP_Laser_WritePulse(uint8_t level);
uint8_t APP_LaserReadPulse(void);
bool APP_Laser_WriteEnergy(uint8_t energy);
uint8_t APP_Laser_ReadEnergy(void);
void APP_Laser_WriteMode(bool state);
bool APP_Laser_ReadPulseMode(void);
void APP_Laser_EnergyReady(bool state);
void APP_Laser_OutEnable(bool state);

bool APP_Laser_WritePulseWidth(uint16_t pulsewidth);
uint16_t APP_LaserReadPulseWidth(void);

bool APP_Laser_IndicatorWriteEnergy(uint8_t energy);
uint8_t APP_Laser_IndicatorReadEnergy(void);
void APP_Laser_IndicatorEnable(bool state);

#endif
