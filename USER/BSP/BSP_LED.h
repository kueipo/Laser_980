#ifndef __BSP_LED_H__
#define __BSP_LED_H__
         
#ifdef __cplusplus
 extern "C" {
#endif

/* LED Num */
typedef enum
{
	LED_0 = 0x00,
	LED_1,
	LED_2,
	LED_ID_MAX,
}ENUM_LED_CHNL_BSP;

/* LED Option Tag */
typedef enum 
{
	LED_OFF = 0,
	LED_ON,
	LED_TOGGLE,
	LED_HOLD,
}LED_Mode_Tag;

typedef struct
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
}BSP_LED_CONFIG;

void BSP_Led_Init(void);
void BSP_Led_DeInit(void);
void BSP_Led_Operate(uint8_t id, uint8_t mode);
void BSP_Led_Config(uint8_t id, uint16_t pwmout);

#ifdef __cplusplus
}
#endif 

#endif


