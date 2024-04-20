#ifndef __APP_FAN_H
#define __APP_FAN_H

#define IN_FAN_MAX_MUNBER		2
#define EX_FAN_MAX_MUNBER		6

#ifndef IN_FAN_MAX_MUNBER
#error "You must define 'IN_FAN_MAX_MUNBER' "
#endif

#ifndef EX_FAN_MAX_MUNBER
#error "You must define 'EX_FAN_MAX_MUNBER' "
#endif

typedef enum {
#if IN_FAN_MAX_MUNBER
	IN_FAN_MODULE,
#endif
#if EX_FAN_MAX_MUNBER
	EX_FAN_MODULE,
#endif
	FAN_MODULE_MAX_NUMBER,
} FAN_MODULE_ENUM;

typedef struct {
	uint8_t AutoPower:1;
	uint8_t Power;
	uint8_t Temperature;
	uint8_t number;
	uint16_t *Speed;
} FanModel_TypeDef;

typedef struct {
	uint8_t Power;
} InFanModel_TypeDef;

void APP_Fan_Init(void);
void APP_Fan_Task(void);
uint8_t Fan_OptPowerVal(Data_OPT opt, FAN_MODULE_ENUM module, uint8_t val);
uint8_t Fan_OptTemperatureVal(Data_OPT opt, FAN_MODULE_ENUM module, uint8_t val);
uint8_t Fan_OptAutoPower(Data_OPT opt, FAN_MODULE_ENUM module, uint8_t val);
uint16_t APP_Fan_OptSpeedVal(Data_OPT opt, FAN_MODULE_ENUM module, uint8_t id, uint16_t val);
#endif  /* __FAN_H */
