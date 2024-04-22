
#ifndef _DEV_CONFIG_H_
#define _DEV_CONFIG_H_

#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include "tim.h"
#include "Debug.h"
#include "main.h"
#include "usart.h"

#define UBYTE   uint8_t
#define UWORD   uint16_t
#define UDOUBLE uint32_t

#define UPDATA_FACTORY_FIRMWARE

/**
 * GPIO read and write
**/
#define DEV_Digital_Write(_pin, _value) 	HAL_GPIO_WritePin(_pin, _value == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET)
#define DEV_Digital_Read(_pin) 						HAL_GPIO_ReadPin(_pin)
#define DEV_Digital_Toggle(_pin)					HAL_GPIO_TogglePin(_pin)

/**
 * UART
**/

typedef enum {
	DEV_MAINUART_INDEX = 0x00,
	DEV_SLAVEUART_INDEX,
	DEV_FAN_INDEX,
	/* Add new val here */
	
	DEV_UART_NUMBER,
} UART_MODULE_INDEX;

/**
 * delay x ms
**/
#define DEV_Delay_ms(__xms) 	HAL_Delay(__xms)

/*-----------------------------------------------------------------------------*/
enum APP_IDX{
	HEART_BEAT,
	APP_TOTAL,
};

enum APP_STAT{
	SUSPEND  = 0,
	READY,
	TIMEOUT,
};

typedef struct
{
	enum APP_STAT State:2;
	uint8_t RunTime:6;
	uint8_t Period;
	void (*current_operation)(void);
}APP;

extern volatile APP App[];

#endif /* _DEV_CONFIG_H_ */
