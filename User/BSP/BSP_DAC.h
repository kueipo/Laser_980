#ifndef __BSP_DAC_H__
#define __BSP_DAC_H__
         
#ifdef __cplusplus
 extern "C" {
#endif

/* KEY Num */
typedef enum
{
	DAC_1    = 0x00,
	DAC_2,
	DAC_ID_MAX,
}ENUM_DAC_CHNL_BSP;

typedef struct
{
	uint32_t MaxVal;
	uint16_t CurVal;
	DAC_HandleTypeDef *hdac;
	uint32_t Channel;
}BSP_DAC_CONFIG;

void BSP_DAC_Init(void);	 
void BSP_DAC_DeInit(void);
void BSP_DAC_Enable(uint8_t id);
void BSP_DAC_Disable(uint8_t id);
void BSP_DAC_Config(uint8_t id, uint16_t usVal);

#ifdef __cplusplus
}
#endif 

#endif
