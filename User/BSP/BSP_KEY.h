#ifndef __BSP_KEY_H__
#define __BSP_KEY_H__

/* KEY Num */
typedef enum
{
	KEY_0,
	KEY_1,
	
	KEY_ID_MAX,
}ENUM_KEY_CHNL_BSP;

/*************KEY ****************/	   
#define KEY_0_PORT                          KEY_0_GPIO_Port
#define KEY_0_PIN                           KEY_0_Pin
     
#define KEY_1_PORT                          FOOT_GPIO_Port
#define KEY_1_PIN                           FOOT_Pin

void BSP_Key_Init(void);
void BSP_Key_DeInit(void);
uint8_t BSP_ReadKeyValue(uint8_t id);

#endif
