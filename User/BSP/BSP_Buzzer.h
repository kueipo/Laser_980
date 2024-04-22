
#ifndef __BSP_BUZZER_H__
#define __BSP_BUZZER_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* BUZZER Num */
typedef enum
{
	BUZZER_0 = 0x00,
	BUZZER_ID_MAX,
} ENUM_BUZZER_ID_BSP;

/* BUZZER Option Tag */
typedef enum
{
	BUZZER_OFF = 0,
	BUZZER_ON,
} BUZZER_OpMode_Tag;

/*************BUZZER_0****************/
#define BUZZER_0_PORT BUZZER_0_GPIO_Port
#define BUZZER_0_PIN 	BUZZER_0_Pin

void BSP_Buzzer_Init(void);
void BSP_Buzzer_DeInit(void);
bool BSP_Buzzer_Operate(uint8_t id, uint8_t mode);

#ifdef __cplusplus
}
#endif

#endif
