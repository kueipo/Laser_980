#ifndef __BSP_POWER_H__
#define __BSP_POWER_H__
         
#ifdef __cplusplus
 extern "C" {
#endif

typedef struct
{
	uint32_t			MaxVal;
	uint32_t			V11;
    DAC_HandleTypeDef  	*hdac;
	uint32_t 			Channel;
}BSP_POWER_CONFIG;

void BSP_Power_Init(void);	 
void BSP_Power_DeInit(void);
void BSP_Power_Enable(void);
void BSP_Power_Disable(void);
void BSP_Power_Config(uint16_t usVal);

#ifdef __cplusplus
}
#endif 

#endif
