#ifndef __BSP_PUMP_H__
#define __BSP_PUMP_H__
         
#ifdef __cplusplus
 extern "C" {
#endif


/* PUMP Num */
typedef enum
{
    PUMP_0 = 0x00,
    PUMP_ID_MAX,
}ENUM_PUMP_CHNL_BSP;

/* PUMP Option Tag */
typedef enum 
{
    PUMP_OFF = 0,
    PUMP_ON,
 
}PUMP_OpMode_Tag;

/*************PUMP_0****************/	   
#define PUMP_0_PORT                          PUMP_0_GPIO_Port
#define PUMP_0_PIN                           PUMP_0_Pin
     
              
void BSP_Pump_Init(void);
void BSP_Pump_DeInit(void);
void BSP_Pump_Operate(uint8_t PumpId, uint8_t PumpOpMode);

#ifdef __cplusplus
}
#endif 

#endif


