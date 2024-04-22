#ifndef __BSP_COOLER_H__
#define __BSP_COOLER_H__

/* FREQ Num */
typedef enum
{
	COOLER_0 = 0x00,
	COOLER_ID_MAX,
} ENUM_COOLER_CHNL_BSP;

/* Cooler Option Tag */
typedef enum
{
	COOLER_OFF = 0,
	COOLER_ON,
} BSP_COOLER_OpMode_Tag;

typedef struct
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
} BSP_COOLER_CONFIG;

void BSP_Cooler_Init(void);	 
void BSP_Cooler_DeInit(void);
bool BSP_Cooler_Operate(uint8_t CoolerId, uint8_t CoolerOpMode);
bool BSP_Cooler_Config(uint8_t CoolerId, uint16_t uiPwmOut);

#endif
