
#ifndef __APP_MOTOR_H
#define __APP_MOTOR_H

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct 
{	
	volatile uint16_t TH_L;
	volatile uint16_t TH_H;
	volatile uint16_t speed;
	volatile bool bError;
}Motor_Struct;

void APP_Motor_Init(void);
void APP_Motor_Task(void);
bool APP_Motor_WriteThreshold(uint8_t id, Motor_Struct *th);
Motor_Struct* APP_Motor_ReadThreshold(uint8_t id);
bool APP_Motor_IsError(uint8_t id);

#ifdef __cplusplus
}
#endif
  
#endif /* __APP_MOTOR_H */
