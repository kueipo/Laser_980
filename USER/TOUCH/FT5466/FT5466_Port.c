
/* Includes ------------------------------------------------------------------*/
#include "FT5466.h"
#include "i2c.h"
#include "main.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define I2C_PORT &hi2c1
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
							   
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/
void FT5466_RST_Control(bool high_or_low)
{
	if (high_or_low)
		HAL_GPIO_WritePin(CPT_RST_GPIO_Port, CPT_RST_Pin, GPIO_PIN_SET);
	else
		HAL_GPIO_WritePin(CPT_RST_GPIO_Port, CPT_RST_Pin, GPIO_PIN_RESET);
}

void FT5466_Delay(uint16_t ms)
{
	HAL_Delay(ms);
}

FT5466_Status_t FT5466_I2C_Init(void)
{
	return FT5466_OK;
}

FT5466_Status_t FT5466_I2C_Write(uint8_t Addr, uint8_t *write_data, uint16_t write_length)
{
	uint8_t Address = Addr;
	switch (HAL_I2C_Master_Transmit(I2C_PORT, Address, write_data, write_length, HAL_MAX_DELAY))
	{
	case HAL_OK:
		return FT5466_OK;
	case HAL_BUSY:
	case HAL_TIMEOUT:
		return FT5466_NotResponse;
	default:
	case HAL_ERROR:
		return FT5466_Error;
	}
}

FT5466_Status_t FT5466_I2C_Read(uint8_t Addr, uint8_t *read_data, uint16_t read_length)
{
	uint8_t Address = Addr;
	switch (HAL_I2C_Master_Receive(I2C_PORT, Address, read_data, read_length, HAL_MAX_DELAY))
	{
	case HAL_OK:
		return FT5466_OK;
	case HAL_BUSY:
	case HAL_TIMEOUT:
		return FT5466_NotResponse;
	default:
	case HAL_ERROR:
		return FT5466_Error;
	}
}
