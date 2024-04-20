#ifndef __BSP_FREQUENCY_H__
#define __BSP_FREQUENCY_H__
         
#ifdef __cplusplus
 extern "C" {
#endif

/* Frequency Tag */
typedef struct
{
	TIM_HandleTypeDef *htim;
	uint32_t Channel;
}BSP_FREQUENCY_CONFIG;
	 
void BSP_Frequency_Init(void);	 
void BSP_Frenquency_DeInit(void);
void BSP_Frenquency_Enable(void);
void BSP_Frenquency_Disable(void);
void BSP_Frenquency_Config(uint16_t Period, uint16_t Pulse);

#ifdef __cplusplus
}
#endif 

#endif
