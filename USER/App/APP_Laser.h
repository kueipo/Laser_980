#ifndef __APP_LASER_H
#define __APP_LASER_H

typedef struct 
{
	volatile uint16_t high;
	volatile uint16_t low;
} ThresholdTypeDef;

void APP_Laser_Init(void);
void APP_LaserOutEnable(bool bState);
void APP_Laser_WritePulseWidth(uint16_t width);
uint16_t APP_Laser_ReadPulseWidth(void);
void APP_Laser_WriteCurThreshold(uint16_t high, uint16_t low);
ThresholdTypeDef * APP_Laser_ReadCurThreshold(void);
void APP_Laser_WriteVolThreshold(uint16_t high, uint16_t low);
ThresholdTypeDef * APP_Laser_ReadVolThreshold(void);

#endif
