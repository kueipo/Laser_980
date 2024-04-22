#ifndef __APP_LED_H
#define __APP_LED_H

/*****************************************************************************
Function name : APP_LED_LightDarkConfig
Description: APP LED模块配置函数，通过调用该函数来操作LED实现各种功能。
Input: 
       LedId->LED的编号;
       OpMode->操作模式 APP_LED_OFF/APP_LED_ON;
       usTimeOut->当OpMode选择APP_LED_ON时，亮灯的时间 ~0表示一直亮灯;
Return: NONE     
Notes:
******************************************************************************/

#define APP_LED_LightDarkConfig(LedId, OpMode, usTimeOut)   APP_LED_Config(LedId, OpMode, usTimeOut, 0, 0)

/*****************************************************************************
Function name : APP_LED_FlickerConfig
Description: APP LED模块配置函数，通过调用该函数来操作LED实现各种功能。
Input:
       LedId->LED的编号;
       usPeriod->当OpMode选择APP_LED_FLASH时，闪烁的周期;
       ucTime->当OpMode选择APP_LED_FLASH时，闪烁的次数ucTime为uint8_t类型，取值255表示一直闪烁;
Return: NONE     
Notes:
******************************************************************************/

#define APP_LED_FlickerConfig(LedId, usPeriod, ucTime)      APP_LED_Config(LedId, APP_LED_FLASH, 0, usPeriod, ucTime)

#define APP_LED_GREEN	LED_0   
#define APP_LED_BLUE	LED_1 
#define APP_LED_RED		LED_2 

/* LED Option Tag */
typedef enum
{
	APP_LED_OFF = 0,
	APP_LED_ON,
	APP_LED_FLASH,
} APP_LED_OpMode_Tag;

/* LED tcb */
typedef struct
{
	volatile uint8_t OpMode;
	volatile uint16_t usTimeCnt;
	volatile uint16_t usTimeOut;
	volatile uint16_t usPeriod;
	volatile uint16_t usDelayCnt;
	volatile uint8_t ucTimes;
	volatile uint8_t HWState; /* LED status */
} APP_LED_TB;

void APP_LED_TimeProc(uint16_t period);
void APP_LED_Init(void);
void APP_LED_Task(void);
void APP_LED_Config(uint8_t id, uint8_t mode, uint16_t timeout, uint16_t period, uint8_t times);
void APP_LED_AllConfig(uint8_t OpMode, uint16_t usTimeOut, uint16_t usPeriod, uint8_t ucTimes);
void APP_LED_ConfigColor(uint8_t red, uint8_t green, uint8_t blue);

#endif
