/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BSP_ADC_H__
#define __BSP_ADC_H__

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define TEMP_TABLES_LENGTH 100

/************* ADC_0 ****************/	
#define ADC_0							(&hadc)
#define ADC_0_DMA_IRQN		DMA1_Channel1_IRQn

typedef enum
{
	LASER_TEMP_CHNL,
	LASER_CUR_CHNL,
	LASER_VOL_CHNL,
	ADC_CHNL_MAX,
} ENUM_ADC_CHNL_INDEX;

/* Adc Tag */
typedef struct
{
	ADC_HandleTypeDef *hadc;
	IRQn_Type IRQn;
} BSP_ADC_CONFIG;

extern const uint16_t NTC50K3950[TEMP_TABLES_LENGTH];
extern const uint16_t NTC10K3950[TEMP_TABLES_LENGTH];

/* External functions --------------------------------------------------------*/
void BSP_Adc_Init(void);
uint16_t BSP_ReadADCVal(uint8_t id);

void BSP_Adc_Enable(void);
void BSP_Adc_Disable(void);

#endif
