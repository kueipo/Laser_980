#ifndef __BSP_LED_H__
#define __BSP_LED_H__
         
#ifdef __cplusplus
 extern "C" {
#endif

//#define USING_LED_GPIO
//#define USING_LED_TIMER

/* LED Num */
typedef enum
{
    LED_0 = 0x00,
    LED_1,
	
    LED_ID_MAX,
}ENUM_LED_CHNL_BSP;

/* LED Option Tag */
typedef enum 
{
    LED_OFF = 0,
    LED_ON,
    LED_TOGGLE,
	LED_HOLD,

}LED_OpMode_Tag;

#ifdef USING_LED_TIMER
	typedef struct
	{
		TIM_HandleTypeDef  	*htim;
		uint32_t 			Channel;
	}BSP_LED_CONFIG;
#else
	/************* LED ****************/	   
	#define LED_R_PORT                          LED_R_GPIO_Port
	#define LED_R_PIN                           LED_R_Pin
		 
	#define LED_B_PORT                          LED_B_GPIO_Port
	#define LED_B_PIN                           LED_B_Pin
#endif

void BSP_Led_Init(void);
void BSP_Led_DeInit(void);
void BSP_Led_Operate(uint8_t LedId, uint8_t LedOpMode);
void BSP_Led_Config(uint8_t LedId, uint16_t uiPwmOut);
#ifdef __cplusplus
}
#endif 

#endif


