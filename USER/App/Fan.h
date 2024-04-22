#ifndef __FAN_H
#define __FAN_H

#include "DEV_Config.h"

typedef enum {
	READ = 0U,
	WRITE,
} FAN_OPT;

typedef enum {
	FAN_MODULE_1 = 0x00,
	FAN_MODULE_2,
	FAN_MODULE_NUMBER,
} FAN_MODULE_INDEX;

void Fan_Init(void);
void Fan_Run(void);
uint8_t FanModule_OptPowerVal(FAN_OPT opt, FAN_MODULE_INDEX index, uint8_t val);
uint8_t FanModule_OptTemperatureVal(FAN_OPT opt, FAN_MODULE_INDEX index, uint8_t val);
uint8_t FanModule_OptAutoPower(FAN_OPT opt, FAN_MODULE_INDEX index, uint8_t val);
#endif  /* __FAN_H */
