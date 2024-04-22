#ifndef __BSP_FAN_H__
#define __BSP_FAN_H__
         
#ifdef __cplusplus
 extern "C" {
#endif

/* FAN Num */
typedef enum
{
	FAN_ID_0 = 0x00,
	FAN_ID_1,
	
	FAN_ID_MAX,
}ENUM_FAN_CHNL_BSP;

/* FAN Option Tag */
typedef enum 
{
	FAN_OFF = 0,
	FAN_ON,
	FAN_HOLD,
}FAN_OpMode_Tag;

typedef struct
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
	TIM_HandleTypeDef *inputhtim;
	uint32_t inputChannel;
}BSP_FAN_CONFIG;

void BSP_Fan_Init(void);
void BSP_Fan_DeInit(void);
void BSP_Fan_Task(void);
void BSP_Fan_Operate(uint8_t id, uint8_t Fanmode);
void BSP_Fan_Config(uint8_t id, uint16_t uiPwmOut);

void BSP_Fan_CaptureOverflow(void);
void BSP_Fan_Capture(TIM_HandleTypeDef *htim);

#ifdef __cplusplus
}
#endif 

#endif


