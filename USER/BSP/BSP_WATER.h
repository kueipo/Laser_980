#ifndef __BSP_WATER_H__
#define __BSP_WATER_H__
         
#ifdef __cplusplus
 extern "C" {
#endif


/* WATER Num */
typedef enum
{
    WATERFLOW_0 = 0x00,
	
    WATERFLOW_ID_MAX,
}ENUM_WATERFLOW_CHNL_BSP;

typedef enum
{
    WATER_HIGH_CHNL	= 0x00,
	WATER_LOW_CHNL,
    WATER_MAX_CHNL,
}ENUM_WATERLEVEL_CHNL_BSP;

/************* WATER ****************/   
#define	BSP_SPEED_DETECTION_TIMX			( &htim2 )

#define	BSP_WATERFLOW_DETECTION_CHNL		TIM_CHANNEL_1
#define BSP_WATERFLOW_DMA_CHNL_IRQn			DMA1_Channel5_IRQn

#define WATER_L_PORT                    	WATER_L_GPIO_Port
#define WATER_L_PIN                     	WATER_L_Pin

#define WATER_H_PORT                    	WATER_H_GPIO_Port
#define WATER_H_PIN                     	WATER_H_Pin

void BSP_Water_Init(void);
uint16_t BSP_ReadWaterSpeed(void);
uint8_t BSP_ReadWaterLevel(void);

#ifdef __cplusplus
}
#endif 

#endif


