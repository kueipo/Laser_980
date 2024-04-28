#ifndef __APP_VOLTAGEDETECTION_H
#define __APP_VOLTAGEDETECTION_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
	INDEX_DC12V = 0x00,
	INDEX_DC5V,
	INDEX_DCLD,
	VOLTAGEDETECTION_MAX,
} ENUM_VOLTAGEDETECTION_TASK;

typedef struct
{
	volatile uint8_t ucThreshold_H;
	volatile uint8_t ucThreshold_L;
	volatile uint16_t usVoltage;
	volatile uint16_t ucRatio;
	volatile uint8_t channel;
	volatile bool bProtect;
} VoltegeDetection_Struct;

void APP_VoltageDetection_Init(void);
void APP_VoltageDetection_Task(void);
uint16_t APP_VoltageDetection_Read(uint8_t id);
bool APP_VoltageDetection_IsError(void);
	
#ifdef __cplusplus
}
#endif

#endif
