#ifndef __APP_FAN_H
#define __APP_FAN_H

#define FAN_MAX_MUNBER		6

typedef enum {
	FAN_MODULE_1 = 0x00,
	FAN_MODULE_NUMBER,
} FAN_MODULE_INDEX;

typedef struct {
	uint8_t AutoPower:1;
	uint8_t Power;
	uint8_t Temperature;
	uint16_t Speed[FAN_MAX_MUNBER];
} FanModel_TypeDef;

void Fan_Init(void);
void Fan_Run(void);
uint8_t Fan_OptPowerVal(Data_OPT opt, uint8_t index, uint8_t val);
uint8_t Fan_OptTemperatureVal(Data_OPT opt, uint8_t index, uint8_t val);
uint8_t Fan_OptAutoPower(Data_OPT opt, uint8_t index, uint8_t val);
uint16_t APP_Fan_OptSpeedVal(Data_OPT opt, uint8_t module, uint8_t index, uint16_t val);
#endif  /* __FAN_H */
