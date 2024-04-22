#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__
         
#ifdef __cplusplus
 extern "C" {
#endif

#define TEMP_TABLES_LENGTH		100

typedef enum
{
	ADC_VREF_CHNL = 0X00,
	MCU_TEMP_CHNL,
	V05_VOL_CHNL,
	V12_VOL_CHNL,
	VLD_VOL_CHNL,
	MOS_TEMP_CHL,

	ADC_CHNL_MAX,
}ENUM_ADC_CHNL_INDEX;

/* Adc Tag */
typedef struct
{
	ADC_HandleTypeDef *hadc;
	IRQn_Type IRQn;
}BSP_ADC_CONFIG;

extern const uint16_t NTC50K3950[TEMP_TABLES_LENGTH];
extern const uint16_t NTC10K3950[TEMP_TABLES_LENGTH];

void BSP_Adc_Init(void);
uint16_t BSP_ReadADCVal(uint8_t channel);

#ifdef __cplusplus
}
#endif 

#endif


