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
		uint8_t ucThreshold_H;
		uint8_t ucThreshold_L;
		uint8_t ucActual;
		uint16_t ucRatio;
		uint8_t channel;
		bool 	bProtect;

	} VoltegeDetection_Struct;

	void APP_VoltageDetection_Init(void);
	void APP_VoltageDetection_Task(void);
	uint8_t APP_VoltageDetectionRead(uint8_t unIndex);
	
#ifdef __cplusplus
}
#endif

#endif
