
#ifndef __BSP_HANDPIECE_H__
#define __BSP_HANDPIECE_H__

/* Handpiece Num */
typedef enum
{
	HANDPIECE_0	= 0x00,
	
	HANDPIECE_ID_MAX,
}ENUM_HANDPIECE_CHNL_BSP;

/************* HANDPIECE 0 ****************/	   
#define HANDPIECE_0_PORT                HANDPIECE_GPIO_Port
#define HANDPIECE_0_PIN                 HANDPIECE_Pin
     
void BSP_Handpiece_Init(void);
uint8_t BSP_ReadHandpieceValue(uint8_t id);

#endif
