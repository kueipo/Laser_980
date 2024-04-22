#ifndef __BSP_MOTOR_H__
#define __BSP_MOTOR_H__
         
#ifdef __cplusplus
 extern "C" {
#endif

/* Moter Num */
typedef enum
{
	MOTOR_0 = 0x00,
	MOTOR_1,
	
	MOTOR_ID_MAX,
}ENUM_MOTOR_CHNL_BSP;


/************* WATER ****************/   
#define	BSP_MOTOR_0_DETECTION_TIMX		( &htim15 )
#define	BSP_MOTOR_0_DETECTION_CHNL		TIM_CHANNEL_1
#define BSP_MOTOR_0_DMA_CHNL_IRQn			DMA1_Channel4_5_IRQn

#define	BSP_MOTOR_1_DETECTION_TIMX		( &htim1 )
#define	BSP_MOTOR_1_DETECTION_CHNL		TIM_CHANNEL_1
#define BSP_MOTOR_1_DMA_CHNL_IRQn			DMA1_Channel2_3_IRQn


#define MOTOR_0_PORT                  RLY5_GPIO_Port
#define MOTOR_0_PIN                   RLY5_Pin

#define MOTOR_1_PORT                  RLY6_GPIO_Port
#define MOTOR_1_PIN                   RLY6_Pin

void BSP_Motor_Init(void);
uint16_t BSP_Motor_ReadSpeed(uint8_t id);
bool BSP_Motor_WriteState(uint8_t id, bool state);
bool BSP_Motor_ReadState(uint8_t id);
	
#ifdef __cplusplus
}
#endif 

#endif


