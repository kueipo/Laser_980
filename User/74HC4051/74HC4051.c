/*
 * Change Logs:
 * Date           Author       Notes
 * 2022-01-12     heguibo      the first version
 */
#include "74HC4051.h"
#include "main.h"

#define S0_MASK 0X01
#define S1_MASK 0X02
#define S2_MASK 0X04

/**
 * IO define
 */
/* #define CS_IO */
#define S0_IO S0_GPIO_Port, S0_Pin
#define S1_IO S1_GPIO_Port, S1_Pin
#define S2_IO S2_GPIO_Port, S2_Pin

#ifdef CS_IO
#define CS(_value) HAL_GPIO_WritePin(CS_IO, _value == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET)
#endif
#define S0(_value) HAL_GPIO_WritePin(S0_IO, _value == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET)
#define S1(_value) HAL_GPIO_WritePin(S1_IO, _value == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET)
#define S2(_value) HAL_GPIO_WritePin(S2_IO, _value == 0 ? GPIO_PIN_RESET : GPIO_PIN_SET)

void CD74HC4051_Init(void)
{
	/* io init */
}

void CD74HC4051_Channel(unsigned char Channel)
{
#ifdef CS_IO
	SC(0);
#endif
	S0((S0_MASK & Channel));
	S1((S1_MASK & Channel));
	S2((S2_MASK & Channel));
#ifdef CS_IO
	SC(1);
#endif
}
