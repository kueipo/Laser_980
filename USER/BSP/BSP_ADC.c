
/* Includes ------------------------------------------------------------------*/
#include "BSP/BSP_Common.h"
								   
/* Configuration table -------------------------------------------------------*/
BSP_ADC_CONFIG const g_stAdcCfg = {
	.hadc = ADC_0,
	.IRQn = ADC_0_DMA_IRQN,
};

#if 0
const uint16_t NTC50K3950[TEMP_TABLES_LENGTH] = {  
	 119,  125,  132,  138,  145,  152,  160,  168,  176,  184, \
	 193,  202,  211,  221,  231,  241,  252,  263,  275,  286, \
	 299,  312,  325,  338,  352,  367,  382,  397,  413,  429, \
	 446,  463,  480,  499,  517,  536,  556,  576,  596,  617, \
	 639,  660,  683,  706,  729,  753,  777,  802,  827,  850, \
	 878,  905,  931,  959,  986, 1014, 1042, 1071, 1100, 1130, \
	1159, 1189, 1219, 1250, 1281, 1312, 1343, 1374, 1406, 1438, \
	1470, 1502, 1534, 1566, 1598, 1631, 1663, 1696, 1728, 1761, \
	1793, 1826, 1858, 1890, 1920, 1954, 1986, 2018, 2050, 2081, \
	2113, 2144, 2175, 2205, 2236, 2266, 2296, 2326, 2355, 2384, \
};
#endif
#if 0
const uint16_t NTC50K3950[TEMP_TABLES_LENGTH] = {
	 159,  167,  175,  184,  193,  202,  212,  222,  232,  243, \
	 255,  267,  279,  292,  305,  318,  332,  347,  362,  378, \
	 394,  411,  428,  446,  464,  483,  502,  522,  543,  564, \
	 586,  609,  632,  656,  680,  705,  731,  757,  784,  811, \
	 840,  868,  898,  928,  959,  990, 1022, 1055, 1088, 1122, \
	1156, 1191, 1226, 1262, 1299, 1336, 1374, 1412, 1450, 1490, \
	1529, 1569, 1609, 1650, 1691, 1733, 1774, 1817, 1859, 1901, \
	1944, 1987, 2031, 2074, 2117, 2161, 2205, 2249, 2292, 2336, \
	2380, 2424, 2468, 2511, 2555, 2598, 2642, 2685, 2728, 2770, \
	2813, 2855, 2897, 2939, 2980, 3021, 3062, 3102, 3142, 3182, \
};
#endif
#if 0
const uint16_t NTC10K3950[TEMP_TABLES_LENGTH] = {
	 706,  738,  771,  818,  852,  887,  923,  960,  998, 1037, \
	1077, 1118, 1160, 1203, 1247, 1291, 1337, 1383, 1430, 1478, \
	1526, 1576, 1626, 1676, 1728, 1779, 1831, 1884, 1937, 1991, \
	2045, 2099, 2154, 2208, 2263, 2318, 2373, 2428, 2482, 2537, \
	2592, 2646, 2700, 2754, 2808, 2861, 2914, 2966, 3018, 3060, \
	3120, 3170, 3220, 3269, 3317, 3365, 3412, 3458, 3504, 3549, \
	3593, 3637, 3679, 3721, 3762, 3802, 3842, 3880, 3918, 3955, \
	3992, 4027, 4062, 4096, 4130, 4162, 4194, 4225, 4256, 4285, \
	4314, 4342, 4370, 4396, 4422, 4448, 4473, 4497, 4521, 4544, \
	4566, 4588, 4610, 4630, 4650, 4670, 4689, 4708, 4726, 4743, \
};
#endif

volatile uint16_t AdcValueTab[ADC_CHNL_MAX] = {0}; /* DMA BUFF */
// float temperature;
// float Vref;

/**
 * @brief  BSP_Adc_Init.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Adc_Init(void)
{
	ADC_HandleTypeDef *hadc;
	IRQn_Type IRQn;

	hadc = g_stAdcCfg.hadc;
	IRQn = g_stAdcCfg.IRQn;

	/* ADC calibration */
	HAL_ADCEx_Calibration_Start(hadc);
	/* Close the ADC DMA channel to prevent repeated DMA interrupt */
	HAL_NVIC_DisableIRQ(IRQn);
	/* Start DMA conversion */
	HAL_ADC_Start_DMA(hadc, (uint32_t *)AdcValueTab, ADC_CHNL_MAX);
}

/**
 * @brief  BSP_ReadADCVal.
 * @note   None.
 * @param  ucIndex.
 * @retval AdcValueTab.
 */
uint16_t BSP_ReadADCVal(uint8_t id)
{
	if (id > ADC_CHNL_MAX)
		return 0xFFFF;

	return AdcValueTab[id];
}

/**
 * @brief  BSP_Adc_Enable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Adc_Enable(void)
{
	ADC_HandleTypeDef *hadc;
	
	hadc = g_stAdcCfg.hadc;
	
	/* Start DMA conversion */
	HAL_ADC_Start_DMA(hadc, (uint32_t *)AdcValueTab, ADC_CHNL_MAX);
}

/**
 * @brief  BSP_Adc_Disable.
 * @note   None.
 * @param  None.
 * @retval None.
 */
void BSP_Adc_Disable(void)
{
	ADC_HandleTypeDef *hadc;
	
	hadc = g_stAdcCfg.hadc;
	
	HAL_ADC_Stop_DMA(hadc);
}
